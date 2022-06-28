#pragma once
#include <type_traits>
#include "BERefCounter.h"

template<typename T>
class BEObject final
{
public:
	BEObject(T* _p = nullptr)
		: refCounter(_p)
	{

	}
	BEObject(const BEObject& _obj)
		: refCounter(_obj.refCounter)
	{
		ObjectAddRef();
	}
	BEObject(BEObject&& _obj) noexcept
		: refCounter(_obj.refCounter)
	{
		_obj.refCounter = nullptr;
	}

	~BEObject() noexcept
	{
		ObjectRelease();
	}

	BEObject& operator = (T* _obj)
	{
		if (refCounter != _obj)
			ObjectRelease();

		refCounter = _obj;
		ObjectAddRef();
		return *this;
	}
	BEObject& operator = (const BEObject& _obj)
	{
		if (refCounter != _obj.refCounter)
			ObjectRelease();

		refCounter = _obj.refCounter;
		ObjectAddRef();
		return *this;
	}
	BEObject& operator = (BEObject&& _obj) noexcept
	{
		if (refCounter != _obj.refCounter)
			ObjectRelease();

		refCounter = _obj.refCounter;
		_obj.refCounter = nullptr;
		return *this;
	}

	template<class U>
	BEObject<U> DynamicCast()
	{
		return dynamic_cast<U*>(refCounter);
	}

	T* operator -> ()
	{
		return static_cast<T*> (refCounter);
	}
	const T* operator -> () const
	{
		return refCounter;
	}

	T* operator * ()
	{
		return refCounter;
	}
	const T* operator * () const
	{
		return refCounter;
	}

	operator T* ()
	{
		return static_cast<T*> (refCounter);
	}
	operator const T* () const
	{
		return refCounter;
	}

	T* Ptr()
	{
		return static_cast<T*> (refCounter);
	}
	const T* Ptr() const
	{
		return refCounter;
	}

private:
	void ObjectAddRef()
	{
		if (refCounter)
			refCounter->AddRef();
	}

	void ObjectRelease()
	{
		if (refCounter && refCounter->ReleaseRef() == 0)
		{
			delete refCounter;
			refCounter = nullptr;
		}
	}

	BERefCounter* refCounter;
};
