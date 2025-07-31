#pragma once

#include <iostream>
#include <Windows.h>

namespace ReaderUpdater {
	void Update();

	uintptr_t ReadOffsetFromJson();
}