/*
 * Copyright (C) 2020 The LineageOS Project
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

#include <fstream>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

using android::base::GetProperty;

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void vendor_load_properties() {
    std::string region = GetProperty("ro.boot.hwc", "");
    std::string hwname = GetProperty("ro.boot.product.hardware.sku", "");

    if (hwname == "lancelot") {
            if (region == "CN") {
                property_override("ro.product.brand", "Redmi");
                property_override("ro.product.model", "Redmi 9 Prime");
                property_override("ro.product.device", "lancelot");
            }else {
                property_override("ro.product.brand", "Redmi");
                property_override("ro.product.model", "Redmi 9");
                property_override("ro.product.device", "lancelot");
        }
    } else if (hwname == "galahad") {
        property_override("ro.product.brand", "Redmi");
        property_override("ro.product.model", "Redmi 9");
        property_override("ro.product.device", "galahad");
    } else if (hwname == "shiva") {
        property_override("ro.product.brand", "POCO");
        property_override("ro.product.model", "POCO M2");
        property_override("ro.product.device", "shiva");
    }
}
