#ifndef __CPP_EVENTS__ABSTRACT_DELEGATE__HPP
#define __CPP_EVENTS__ABSTRACT_DELEGATE__HPP

#include "../../FastDelegate/FastDelegate.h"

namespace Cpp {
//------------------------------------------------------------------------------
//! Value type that represents arbitrary delegate in a common form.
class AbstractDelegate
{
public:
	AbstractDelegate() : d_() {}
	AbstractDelegate(fastdelegate::DelegateMemento const & d) : d_(d) {}
	
	template<class D> AbstractDelegate(D const & deleg)
		: d_(deleg.GetMemento())
	{}

	template<class T, class Y> AbstractDelegate(T obj, Y pmf)
		: d_(fastdelegate::MakeDelegate(obj, pmf).GetMemento())
	{}

	bool isNull() const { return d_.empty(); }
	void clear() { d_.clear(); }

	bool operator<(AbstractDelegate const & r) const { return d_.IsLess(r.d_); }
	bool operator>(AbstractDelegate const & r) const { return r.d_.IsLess(d_); }
	bool operator==(AbstractDelegate const & r) const { return d_.IsEqual(r.d_); }
	bool operator!=(AbstractDelegate const & r) const { return !d_.IsEqual(r.d_); }
	bool operator>=(AbstractDelegate const & r) const { return !d_.IsLess(r.d_); }
	bool operator<=(AbstractDelegate const & r) const { return !r.d_.IsLess(d_); }

	template<class D> D castToDelegate() const
	{
		D retVal;
		retVal.SetMemento(d_);
		return retVal;
	}
private:
	fastdelegate::DelegateMemento d_;
};
//------------------------------------------------------------------------------
} //namespace Cpp

#endif //ABSTRACT_DELEGATE__HPP