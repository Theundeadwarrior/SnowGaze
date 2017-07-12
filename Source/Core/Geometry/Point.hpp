
namespace Core
{
	template <typename T, typename U>
	inline Point3<T> operator*(U f, const Point3<T>& p)
	{
		return p * f;
	}
}