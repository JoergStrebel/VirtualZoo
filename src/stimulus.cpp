// SPDX-FileCopyrightText: 2023 Jörg Strebel <email>
// SPDX-License-Identifier: Apache-2.0

#include "stimulus.h"

/**
 * @todo write docs
 */

stimulus::stimulus(const std::string& typedesc, const void* data): typedesc(typedesc)
    {
        this->data=data;
    }

stimulus::~stimulus()
{
}


const void* stimulus::get_data() const {
    return data;
}

const std::string stimulus::get_id() const {
    return typedesc;
}

