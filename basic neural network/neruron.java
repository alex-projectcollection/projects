package newneural_network;

public class neruron {

	private char s = ' ';
	private double out = 0;
	private double in = 0;

	// constractor
	public neruron() {
		this.s = ' ';
		this.out = 0;
		this.in = 0;

	}

	public neruron(char s, double in, double out) {

		this.s = s;
		this.in = in;
		this.out = out;

	}

	// getters and setters
	public char getS() {
		return s;
	}

	public void setS(char s) {
		this.s = s;
	}

	public double getOut() {
		return out;
	}

	public void setOut(double out) {
		this.out = out;
	}

	public double getIn() {
		return in;
	}

	public void setIn(double in) {
		this.in = in;
	}

}
