package restApi;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CityService {
	private Map<Integer, City> allCities = new HashMap<>();

	public List<City> getAllCities() {
		return new ArrayList<>(allCities.values());
	}

	public City getCity(Integer id) {
		return allCities.get(id);
	}

	public City createCity(float x, float y) {
		City newCity = new City(x, y);
		allCities.put(newCity.getId(), newCity);
		return newCity;
	}

	public City createCity() {
		City newCity = new City();
		allCities.put(newCity.getId(), newCity);
		return newCity;
	}
}
