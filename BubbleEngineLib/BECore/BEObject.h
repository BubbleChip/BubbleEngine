#pragma once
#include <type_traits>
#include "BERefCounter.h"

template<class T>
concept HasRefCounter = std::is_convertible_v<T*, BERefCounter*>;

template<class T, class U>
concept Convertible = std::is_convertible_v<T*, U*>;

template<HasRefCounter T>
class BEObject final
{
public:
	BEObject(T* p = nullptr)
		: target(p)
	{
		InternalAddRef();
	}
	BEObject(const BEObject& obj)
		: target(obj.target)
	{
		InternalAddRef();
	}
	BEObject(BEObject&& obj) noexcept
		: target(obj.target)
	{
		obj.target = nullptr;
	}

	// convertible
	template<Convertible U>
	BEObject(U* p)
		: target(p)
	{
		InternalAddRef();
	}
	template<Convertible U>
	BEObject(const BEObject<U>& obj)
		: target(obj.target)
	{
		InternalAddRef();
	}
	template<Convertible U>
	BEObject(BEObject<U>&& obj) noexcept
		: target(obj.target)
	{
		obj.target = nullptr;
	}

	~BEObject() noexcept
	{
		InternalRelease();
	}

	BEObject& operator = (T* obj)
	{
		if (target != obj)
			InternalRelease();

		target = obj;
		InternalAddRef();
		return *this;
	}
	BEObject& operator = (const BEObject& obj)
	{
		if (target != obj.target)
			InternalRelease();

		target = obj.target;
		InternalAddRef();
		return *this;
	}
	BEObject& operator = (BEObject&& obj) noexcept
	{
		if (target != obj.target)
			InternalRelease();

		target = obj.target;
		obj.target = nullptr;
		return *this;
	}

	// convertible
	template<Convertible U>
	BEObject& operator = (U* obj)
	{
		if (target != obj)
			InternalRelease();

		target = obj;
		InternalAddRef();
		return *this;
	}
	template<Convertible U>
	BEObject& operator = (const BEObject<U>& obj)
	{
		if (target != obj.target)
			InternalRelease();

		target = obj.target;
		InternalAddRef();
		return *this;
	}
	template<Convertible U>
	BEObject& operator = (BEObject<U>&& obj) noexcept
	{
		if (target != obj.target)
			InternalRelease();

		target = obj.target;
		obj.target = nullptr;
		return *this;
	}

	template<class U>
	BEObject<U> DynamicCast()
	{
		return dynamic_cast<U*>(target);
	}

	T* operator -> ()
	{
		return target;
	}
	const T* operator -> () const
	{
		return target;
	}

	T* operator * ()
	{
		return target;
	}
	const T* operator * () const
	{
		return target;
	}

	operator T* ()
	{
		return target;
	}
	operator const T* () const
	{
		return target;
	}

	T* Ptr()
	{
		return target;
	}
	const T* Ptr() const
	{
		return target;
	}

private:
	void InternalAddRef()
	{
		if (target)
			target->AddRef();
	}

	void InternalRelease()
	{
		if (target && target->ReleaseRef() == 0)
		{
			delete target;
			target = nullptr;
		}
	}

	T* target;
};
