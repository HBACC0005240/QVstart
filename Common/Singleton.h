#ifndef WZQ_Singleton_H
#define WZQ_Singleton_H

template <typename T>
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() {}

	static T* instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new T();
		}

		return m_pInstance;
	}
	static void destory()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	// ·ÀÖ¹µ¥¼þ¸´ÖÆ.
	Singleton(const Singleton& copy) {};
	void operator = (const Singleton& rhs) {};

	static T*	m_pInstance;
};
template <typename T>
T* Singleton<T>::m_pInstance = 0;
#endif//WZQ_Singleton_H
