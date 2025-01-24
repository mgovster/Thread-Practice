# Thread-Practice
One of my many practice programs using C++ where there is a Part worker and Product worker with one shared mutex lock. Only one part worker or one product worker can go at a time until it finishes it's work. Upon starting each batch, it locks the lock and when it finishes it unlocks.
