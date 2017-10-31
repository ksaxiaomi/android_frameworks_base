/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CONDITION_WIZARD_H
#define CONDITION_WIZARD_H

#include "ConditionTracker.h"
#include "condition_util.h"

namespace android {
namespace os {
namespace statsd {

// Held by MetricProducer, to query a condition state with input defined in EventConditionLink.
class ConditionWizard : public virtual android::RefBase {
public:
    ConditionWizard(){};  // for testing
    ConditionWizard(std::vector<sp<ConditionTracker>>& conditionTrackers)
        : mAllConditions(conditionTrackers){};

    virtual ~ConditionWizard(){};

    // Query condition state, for a ConditionTracker at [conditionIndex], with [conditionParameters]
    // [conditionParameters] mapping from condition name to the HashableDimensionKey to query the
    //                       condition.
    // The ConditionTracker at [conditionIndex] can be a CombinationConditionTracker. In this case,
    // the conditionParameters contains the parameters for it's children SimpleConditionTrackers.
    virtual ConditionState query(
            const int conditionIndex,
            const std::map<std::string, HashableDimensionKey>& conditionParameters);

private:
    std::vector<sp<ConditionTracker>> mAllConditions;
};

}  // namespace statsd
}  // namespace os
}  // namespace android
#endif  // CONDITION_WIZARD_H
