import java.io.*;
import java.util.*;

public class Fenwick {

	class FenwickTree {
		int n;
		long[] values;

		FenwickTree(int n) {
			this.n = n;
			values = new long[n];
		}

		long get(int r) {
			long res = 0;
			while (r >= 0) {
				res += values[r];
				r = (r & (r + 1)) - 1;
			}
			return res;
		}

		void update(int pos, long value) {
			while (pos < n) {
				values[pos] += value;
				pos = (pos | (pos + 1));
			}
		}

		long get(int l, int r) {
			return get(r) - get(l - 1);
		}
	}

	void stress() {
		Random rnd = new Random(123);
		for (int it = 0; it < 1000; it++) {
			System.err.println(it);
			int n = 1 + rnd.nextInt(100);
			long[] a = new long[n];
			FenwickTree fenwick = new FenwickTree(n);
			for (int q = 0; q < 1000; q++) {
				if (rnd.nextBoolean()) {
					int fr = rnd.nextInt(n);
					int to = rnd.nextInt(n);
					if (to < fr) {
						int tmp = fr;
						fr = to;
						to = tmp;
					}
					long r1 = 0;
					for (int i = fr; i <= to; i++) {
						r1 += a[i];
					}
					long r2 = fenwick.get(fr, to);
					if (r1 != r2) {
						throw new AssertionError(r1 + " " + r2);
					}
				} else {
					int pos = rnd.nextInt(n);
					int val = rnd.nextInt(100) -50;
					a[pos] += val;
					fenwick.update(pos, val);
				}
			}
		}
	}

	void solve() {
		stress();
	}

	InputReader in;
	PrintWriter out;

	void runIO() {
		in = new InputReader(System.in);
		out = new PrintWriter(System.out);

		solve();

		out.close();
	}

	void run() {
		in = new InputReader(new File("input.txt"));
		try {
			out = new PrintWriter(new File("output.txt"));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		solve();

		out.close();
	}

	public static void main(String[] args) {
		new Fenwick().runIO();
	}

	class InputReader {
		BufferedReader bf;
		StringTokenizer st;

		InputReader(File f) {
			try {
				bf = new BufferedReader(new FileReader(f));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}

		InputReader(InputStream s) {
			bf = new BufferedReader(new InputStreamReader(s));
		}

		String next() {
			while (st == null || !st.hasMoreElements()) {
				String s;
				try {
					s = bf.readLine();
				} catch (IOException e) {
					return null;
				}
				if (s == null)
					return null;
				st = new StringTokenizer(s);
			}
			return st.nextToken();
		}

		int nextInt() {
			return Integer.parseInt(next());
		}

		long nextLong() {
			return Long.parseLong(next());
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}

		boolean hasMoreElements() {
			while (!st.hasMoreElements()) {
				String s;
				try {
					s = bf.readLine();
				} catch (IOException e) {
					return false;
				}
				if (s == null)
					return false;
				st = new StringTokenizer(s);
			}
			return true;
		}
	}
}