public class DateException extends Exception {
  private String message;
  public DateException(String message) {
    super(message); // 调用父类的构造方法
    this.message = message;
  }
  public String getMessage() {
    return message;
  }
}
