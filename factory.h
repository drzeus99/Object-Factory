//
//  factory.h
//  lmpsdata++
//
//  Created by Zachary Kraus on 7/17/14.
//
//

#include <map>
#include "singleton.h"
#include <stdexcept>
#ifndef lmpsdata___factory_h
#define lmpsdata___factory_h
/**a singleton object factory that allows the user to create and copy objects using a
string name that has been associated with an object*/
//this class is written in the style of the Curiously recurring template pattern
//is thread safe unless one thread is creating/copying an object and another is inserting an object into a table.
template <class T>
class factory: public singleton<factory<T> >
{
	factory() {}
	std::map<const std::string, T*> table; /**<stores the string-object associations */
	~factory() //assuming this is called automatically at program termination
	{//since instance is static.
		//we need to clean up the pointers taken up in table
		//note even though T* probabbly has a reference manager
		//it will not be used in the destructor
		for (typename std::map<const std::string, T*>::iterator it=table.begin(); it!=table.end(); it++) {
			delete it->second;
		}
	}
	//the combination of friend class and new_instance being private
	//ensures that this version of factory is truly a singleton.
	friend class singleton<factory<T> >;
	static factory* new_instance()
	{
		return new factory;
	}
public:
    /** @brief shows whether the table storing the string-object associations is empty
     *
     * @return true if the table is empty and false otherwise
     */
	bool isempty()
	{
		return table.empty();
	}

    /** @brief inserts a string-object association into the table storing the associations
     *
     * @param name a c-string
     * @param object a pointer of type T
     *
     */
	void insert(const char* name, T* object)
	{
		table[name]=object;
	}

    /** @brief inserts a string-object association into the table storing the associations
     *
     * @param name a string
     * @param object a pointer of type T
     *
     */
	void insert(const std::string &name, T* object)
	{
		table[name] = object;
	}

    /** @brief creates an object of type T
     * using the supplied c-string to locate the string-object association in table.
     * if the association doesn't exist, throws a std::runtime_error.
     * @param name a c-string
     * @return a pointer to a newly created object of type T
     *
     */
	T* create(const char* name)
	{
		typename std::map<const std::string, T*>::iterator it = table.find(name);
		if (it != table.end()) {
            T* new_object = it->second->new_instance();
            return new_object;
        }
        else
            throw std::runtime_error("that object type doesn't exist in this factory");
	}

    /** @brief creates an object of type T
     * using the supplied string to locate the string-object association in table.
     * if the association doesn't exist, throws a std::runtime_error.
     * @param name a string
     * @return a pointer to a newly created object of type T
     *
     */
	T* create(const std::string &name)
	{
		typename std::map<const std::string, T*>::iterator it = table.find(name);
		if (it != table.end()) {
			T* new_object= it->second->new_instance();
			return new_object;
		}
		else
			throw std::runtime_error("that object type doesn't exist in this factory");
	}

    /** @brief copies an object of type T
     * using the supplied c-string to locate the string-object association in table.
     * if the association doesn't exist, throws a std::runtime_error.
     * @param name a c-string
     * @param object to be copied
     * @return a copy of the inputed object. the copy is a new pointer of type T.
     *
     */
	T* copy(const char* name, T* object)
	{
	    typename std::map<const std::string, T*>::iterator it = table.find(name);
	    if (it != table.end()) {
            T* new_object = it->second->copy_instance(object);
            return new_object;
	    }
	    else
            throw std::runtime_error("that object type doesn't exist in this factcory");

	}

	/** @brief copies an object of type T
     * using the supplied string to locate the string-object association in table.
     * if the association doesn't exist, throws a std::runtime_error.
     * @param name a string
     * @param object to be copied
     * @return a copy of the inputed object. the copy is a new pointer of type T.
     *
     */
	T* copy(const std::string &name, T* object)
	{
		typename std::map<const std::string, T*>::iterator it = table.find(name);
		if (it != table.end()) {
			T* new_object= it->second->copy_instance(object);
			return new_object;
		}
        else
            throw std::runtime_error("that object type doesn't exist in this factory");
	}
};


#endif
