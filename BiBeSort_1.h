
namespace umnas
{
	template<typename Clock>
	class chasici
	{
	public:
		typedef Clock clock_type;
		typedef typename Clock::time_point time_point_type;
		typedef typename Clock::duration duration_type;

		chasici &start()
		{
			starttime_ = clock_type::now();
			return *this;
		}
		chasici &stop()
		{
			duration_ += clock_type::now() - starttime_;
			return *this;
		}
		chasici &update()
		{
			time_point_type now = clock_type::now();
			duration_ += now - starttime_;
			starttime_ = now;
			return *this;
		}
		chasici &reset()
		{
			duration_ = duration_type::zero();
			return *this;
		}

		duration_type const &duration() const
		{
			return duration_;
		}

	private:
		time_point_type starttime_ = clock_type::now();
		duration_type duration_ = duration_type::zero();


	};
}