#pragma once

#include <atomic>

namespace SnowGaze
{

	class ReferenceCounted
	{
	public:
		ReferenceCounted() { m_ReferenceCount = 0; }
		ReferenceCounted(const ReferenceCounted& rhs) = delete;
		ReferenceCounted& operator=(const ReferenceCounted& rhs) = delete;

	private:
		std::atomic<uint32_t> m_ReferenceCount;
	};

	//template<typename T, typename std::enable_if_t<std::is_base_of<ReferenceCounted, T>>>
	//class Reference
	//{
	//public:
	//	Reference(T* ptr) {ptr-}

	//private:
	//	T* ptr;
	//};

}