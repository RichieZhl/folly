/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <folly/fibers/detail/AtomicBatchDispatcher.h>

#include <cassert>

#include <fmt/fmt/core.h>

namespace folly {
namespace fibers {
namespace detail {

std::string createABDTokenNotDispatchedExMsg(
    const std::vector<size_t>& vecTokensNotDispatched) {
  size_t numTokensNotDispatched = vecTokensNotDispatched.size();
  assert(numTokensNotDispatched > 0);
  size_t numSeqNumToPrint =
      (numTokensNotDispatched > 10 ? 10 : numTokensNotDispatched);
  std::string strInputsNotFound = fmt::format("{}", vecTokensNotDispatched[0]);
  for (size_t i = 1; i < numSeqNumToPrint; ++i) {
    strInputsNotFound += fmt::format(", {}", vecTokensNotDispatched[i]);
  }
  if (numSeqNumToPrint < numTokensNotDispatched) {
    strInputsNotFound += "...";
  }
  return fmt::format(
      "{} input tokens (seq nums: {}) destroyed before calling dispatch",
      numTokensNotDispatched,
      strInputsNotFound);
}

std::string createUnexpectedNumResultsABDUsageExMsg(
    size_t numExpectedResults, size_t numActualResults) {
  return fmt::format(
      "Unexpected number of results ({}) returned from dispatch function, "
      "expected ({})",
      numActualResults,
      numExpectedResults);
}

} // namespace detail
} // namespace fibers
} // namespace folly
