package restApi;

public class City {
	private int id;
	private float x;
	private float y;

	public City() {
		this.x = (float) (Math.random() * 500);
		this.y = (float) (Math.random() * 500);
		this.id = this.hashCode();
	}

	public City(float x, float y) {
		this.x = x;
		this.y = y;
		this.id = this.hashCode();
	}

	public int getId() {
		return id;
	}

	public float getX() {
		return x;
	}

	public float getY() {
		return y;
	}

	public void setId(int id) {
		this.id = id;
	}

	public void setX(float x) {
		this.x = x;
	}

	public void setY(float y) {
		this.y = y;
	}

}
