// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include <map>
#include <iostream>
#include <assert.h>

// ----------------------------------------------------------------------------
// GTimeDiff
// ----------------------------------------------------------------------------
/*
 * MILESTONE (e.g. int)
 * CLOCK     (e.g. std::chrono::high_resolution_clock::time_point)
 * DIFF      (e.g. std::chrono::high_resolution_clock::duration)
 * TIMER     (e.g. std::chrono::high_resolution_clock)
 *
 * For more information, see GTimeDiffNull
 */
template <typename MILESTONE, typename CLOCK, typename DIFF, typename TIMER>
class GTimeDiff {
  struct Key {
    MILESTONE from_;
    MILESTONE to_;

    bool operator < (const Key& rhs) const {
      if (this->from_ < rhs.from_) return true;
      if (this->from_ > rhs.from_) return false;
      if (this->to_ < rhs.to_) return true;
      return false;
    }

    bool operator == (const Key& rhs) const {
      return (from_ == rhs.from_) && (to_ == rhs.to_);
    }

    struct Hash {
      size_t operator()(const Key &key) const {
        return std::hash<MILESTONE>()(key.from_) ^ std::hash<MILESTONE>()(key.to_);
      }
    };
  };

  struct Data {
  public:
    int count_;
    DIFF totalElapsed_;
  };

  typedef std::map<Key, Data> ReportMap;

public:
  TIMER timer_;
  ReportMap reportMap_;
  MILESTONE lastMilestone_;
  CLOCK lastClock_;

public:
  GTimeDiff(MILESTONE startMilestone = 0) {
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

  void check(MILESTONE milestone) {
    check(milestone, timer_.now());
  }

  void check(MILESTONE milestone, CLOCK now) {
    Key key;
    key.from_ = lastMilestone_;
    key.to_ = milestone;

    Data &data = reportMap_[key];
    data.count_++;
    data.totalElapsed_ += DIFF(now - lastClock_);

    lastMilestone_ = milestone;
    lastClock_ = now;
  }

  virtual void report(bool autoClear = true, int div = 1000000, std::ostream* os = nullptr) {
    if (os == nullptr) os = &std::cout;
    *os << "beg\t\tend\t\tcount\t\telapsed\t\taverage\n";
    for (auto it = reportMap_.begin(); it != reportMap_.end(); it++) {
      Key key = it->first;
      if (key.from_ == 0) continue;
      Data data = it->second;
      assert(data.count_ != 0);
      DIFF elapsed = data.totalElapsed_ / div;
      DIFF avg = elapsed / data.count_;
      *os << key.from_
        << "\t\t" << key.to_
        << "\t\t" << data.count_
        << "\t\t" << elapsed
        << "\t\t" << avg
        << std::endl;
    }
    if (autoClear) clear();
  }
};
