public class Main {
    private static void app(){
        int a = 0, b = 3, c = 3;

        for (int i=0; i<100000000; i++){
            a += b*2 + c - i;
        }
    }

    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();

        app();

        long endTime = System.currentTimeMillis();

        System.out.println("command took " + (endTime - startTime) + " ms");
    }
}