//
//  singleton.h
//  lmpsdata++
//
//  Created by Zachary Kraus on 7/20/14.
//
//

#ifndef lmpsdata___singleton_h
#define lmpsdata___singleton_h
/**a class that is inherited by another class to enable singleton behavior.*/
//uses the curriously recurring template pattern to allow the child class to inherit the singleton behavior.
template <class S>
class singleton
{
protected:
	static S* instance; /**< stores a single pointer of the child class */
	singleton() {}
public:
    /** @brief factory method for the singleton class which ensures one and only one pointer.
     * uses curiously recurring template pattern to call a factory method from the child class
     * @return a pointer of the child class
     *
     */
	static S* get_instance()
	{
		if (instance == 0) {
			instance = S::new_instance();
		}
		return instance;
	}
};

template <class S>
S* singleton<S>::instance=0;


#endif
