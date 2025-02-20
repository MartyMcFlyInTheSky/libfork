// Copyright © Conor Williams <conorwilliams@outlook.com>

// SPDX-License-Identifier: MPL-2.0

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <catch2/catch_test_macros.hpp>

#include "libfork/detail/utility.hpp"

// NOLINTBEGIN No linting in tests

consteval void foo() {
  ASSERT(true, "test macro valid in constexpr context.");
  DEBUG_TRACKER("test macro valid in constexpr context.");
}

// NOLINTEND