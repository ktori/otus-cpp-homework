//
// Created by victoria on 31.05.20.
//

#pragma once

#include <memory>
#include <forward_list>

namespace bulk
{

	/**
	 * Interface for observer of type T
	 * @tparam T Type of data the observer can process
	 */
	template<typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;

		virtual void update(const T& data) = 0;
	};

	/**
	 * Interface for observable of type T
	 * @tparam T Data type that is emitted by observable
	 */
	template<typename T>
	class Observable
	{
	public:
		virtual ~Observable() = default;

		virtual void add_subscriber(const std::shared_ptr<Observer<T>>& observer) = 0;
	};

	/**
	 * Abstract implementation of Observable that stores forward_list of weak pointers to Observers
	 * @tparam T Observable data type
	 */
	template<typename T>
	class AbstractObservable : public Observable<T>
	{
	public:
		~AbstractObservable() override = default;

		/**
		 * Adds a subscriber (observer) to the list
		 * @param observer Observer to be added
		 */
		void add_subscriber(const std::shared_ptr<Observer<T>>& observer) override
		{
			observers.push_front(observer);
		}

		/**
		 * Emit data, notifying each observer
		 * @param data Data to be emitted
		 */
	protected:
		void emit(const T& data)
		{
			auto previous = observers.before_begin();
			for (auto it = observers.begin(); it != observers.end();)
			{
				auto observer = it->lock();
				if (!observer)
				{
					it = observers.erase_after(previous);
					continue;
				}

				observer->update(data);
				++it;
			}
		}

	private:
		std::forward_list<std::weak_ptr<Observer<T>>> observers{};
	};

}