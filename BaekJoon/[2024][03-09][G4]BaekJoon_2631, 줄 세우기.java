import java.util.*;

public class Main {
    static Scanner scanner = new Scanner(System.in);
    static ArrayList<Integer> list = new ArrayList<>();
    static int n;
    static int[] dp;
    static int answer = 0;

    static void init() {
        n = scanner.nextInt();
        dp = new int[n];
        for (int i = 0; i < n; i++) {
            list.add(scanner.nextInt());
        }
    }

    static void sol() {
        for (int i = 0; i < n; i++) {
            dp[i] = 1; // 반드시 1명은 옮기지 않아도 된다.
            for (int j = 0; j <= i; j++) {
                // 맨 앞부터 본인까지 탐색하여 증가하는 부분 수열이 이루어진다면 교체한다. (큰 순서로)
                if (list.get(i) > list.get(j) && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            answer = Math.max(answer, dp[i]); // 모든 경우에서 가장 큰 증가하는 부분 수열이 움직이지 않아도 되는 인원
        }
    }

    public static void main(String[] args) {
        init();
        sol();
        System.out.println(n - answer);
    }
}