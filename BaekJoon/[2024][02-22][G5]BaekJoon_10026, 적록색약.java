import javax.naming.PartialResultException;
import java.awt.image.ImageProducer;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.AbstractMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class Main {

    static int N;
    static String str;
    static char[][] arr;
    static boolean[][] visit;
    static int[] next_x = {-1, 1, 0, 0};
    static int[] next_y = {0, 0, 1, -1};
    static int rgbAnswer = 0;
    static int noRgbAnswer = 0;

    public static void main(String[] args) throws IOException {
        BufferedReader init = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(init.readLine());
        arr = new char[N][N];
        visit = new boolean[N][N];

        for (int i = 0; i < N; i++) {
            str = init.readLine();
            for (int j = 0; j < N; j++) {
                arr[i][j] = str.charAt(j);
            }
        }

        int cnt = 0;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                if (!visit[y][x]) {
                    BFS(x, y);
                    cnt++;
                }
            }
        }
        System.out.printf("%d ", cnt);

        // 방문 초기화
        cnt = 0;
        visit = new boolean[N][N];

        // 적록색맹은 구별하지 못하는 색
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                if (arr[y][x] == 'R') {
                    arr[y][x] = 'G';
                }
            }
        }

        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                if (!visit[y][x]) {
                    BFS(x, y);
                    cnt++;
                }
            }
        }
        System.out.println(cnt);
    }

    public static void BFS(int x, int y) {
        LinkedList<int[]> list = new LinkedList<>();
        list.add(new int[]{x, y});
        visit[y][x] = true;

        while (!list.isEmpty()) {
            // 현재 좌표
            int curx = list.getFirst()[0];
            int cury = list.getFirst()[1];
            list.removeFirst(); // 현재위치 추출 완료

            for (int i = 0; i < 4; i++) {
                // 상하 좌우
                int nx = curx + next_x[i];
                int ny = cury + next_y[i];

                // 다음 좌표가 범위안에 있고, 방문하지 않은 곳인가?
                if (nx > -1 && ny > -1 && nx < N && ny < N && !visit[ny][nx]) {
                    // 색이 같다면
                    if (arr[cury][curx] == arr[ny][nx]) {
                        visit[ny][nx] = true; // 방문표시
                        list.add(new int[]{nx, ny}); // 여기서도 찾아보자
                    }
                }
            }
        }
    }
}