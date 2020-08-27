// ----------------------------------------------------------------------------
//
// G Library
//
// http://gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include <cassert>
#include <chrono>
#include <iostream>
#include <map>

// ----------------------------------------------------------------------------
// GTimeDiff
// ----------------------------------------------------------------------------
class GTimeDiff {
	typedef int Milestone;

	typedef std::chrono::high_resolution_clock::time_point Clock;

	typedef std::chrono::high_resolution_clock::duration Diff;

	typedef std::chrono::high_resolution_clock Timer;

	struct Key {
		Milestone from_;
		Milestone to_;

		bool operator < (const Key& rhs) const {
		  if (this->from_ < rhs.from_) return true;
		  if (this->from_ > rhs.from_) return false;
		  if (this->to_ < rhs.to_) return true;
		  return false;
		}
	};

	struct Data {
	public:
		int count_;
		Diff totalElapsed_;
	};

	typedef std::map<Key, Data> ReportMap;

public:
	Timer timer_;
	ReportMap reportMap_;
	Milestone lastMilestone_;
	Clock lastClock_;

public:
	GTimeDiff(Milestone startMilestone = 0) {
		clear();
		if (startMilestone != 0)
			check(startMilestone);
	}

	virtual ~GTimeDiff() {
		if (reportMap_.size() > 0)
			report(true);
	}

	void clear() {
		reportMap_.clear();
		lastMilestone_ = 0;
		lastClock_ = timer_.now();
	}

	void check(Milestone milestone) {
		check(milestone, timer_.now());
	}

	void check(Milestone milestone, Clock now) {
		Key key;
		key.from_ = lastMilestone_;
		key.to_ = milestone;

		Data &data = reportMap_[key];
		data.count_++;
		data.totalElapsed_ += Diff(now - lastClock_);

		lastMilestone_ = milestone;
		lastClock_ = now;
	}

	virtual void report(int div = 1000000, bool autoClear = true, std::ostream* os = nullptr) {
		if (os == nullptr) os = &std::cout;
		*os << "beg\t\tend\t\tcount\t\telapsed\t\taverage\n";
		for (auto it = reportMap_.begin(); it != reportMap_.end(); it++) {
			Key key = it->first;
			if (key.from_ == 0) continue;
			Data data = it->second;
			assert(data.count_ != 0);
			Diff elapsed = data.totalElapsed_ / div;
			Diff avg = elapsed / data.count_;
			*os << key.from_
				<< "\t\t" << key.to_
				<< "\t\t" << data.count_
				<< "\t\t" << elapsed.count()
				<< "\t\t" << avg.count()
				<< std::endl;
		}
		if (autoClear) clear();
	}
};
