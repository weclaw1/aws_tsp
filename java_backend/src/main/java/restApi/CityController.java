package restApi;

import static spark.Spark.*;
import spark.Request;
import spark.Response;
import spark.Route;

public class CityController {
	public CityController(final CityService cityservice) {
		get("/city", "application/json", new Route() {
			@Override
			public Object handle(Request request, Response response) throws Exception {
				return cityservice.getAllCities();
			}
		}, new JsonTransformer());

		post("/city", "application/json", new Route() {
			@Override
			public Object handle(Request request, Response response) throws Exception {
				if (request.queryParams().isEmpty()) {
					return cityservice.createCity();
				} else {
					return cityservice.createCity(Float.parseFloat(request.queryParams("x")),
							Float.parseFloat(request.queryParams("y")));
				}
			}
		}, new JsonTransformer());

		get("/city/:id", "application/java", new Route() {
			@Override
			public Object handle(Request request, Response response) throws Exception {
				int id = Integer.parseInt(request.params(":id"));
				City city = cityservice.getCity(id);
				if (city != null) {
					return city;
				}
				response.status(400);
				return "No city with id: " + id + " found!";
			}
		}, new JsonTransformer());

	}
}
