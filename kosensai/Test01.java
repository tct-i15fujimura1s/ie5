// Test01.java
import javax.sound.sampled.*;
class Test01 {
  public static void main(String[] args_){
    try{
      int sampleRate = 44100;
      int seconds = 2;
      byte[] wave_data= new byte[sampleRate*seconds];

      int pwmDiv = 100;

      for(int i=0;i<wave_data.length; i+=80){
        for (int j=0; j<20; j++) wave_data[i+j] = 0;
        i += 20;

        for (int j=0; j<10; j++) wave_data[i+j] = 0;
        i += 12;
        for (int j=0; j<10; j++) wave_data[i+j] = 100;
        i += 25;

        for (int j=0; j<25; j++) wave_data[i+j] = 0;
        i += 25;
        for (int j=0; j<25; j++) wave_data[i+j] = 100;
        i += 25;

        for (int j=0; j<50; j++) wave_data[i+j] = 100;
        i += 50;
      }

      AudioFormat   frmt= new AudioFormat(sampleRate,8,1,true,false);
      DataLine.Info info= new DataLine.Info(Clip.class,frmt);
      Clip          clip= (Clip)AudioSystem.getLine(info);
      clip.open(frmt,wave_data,0,wave_data.length);
      clip.start();

      Thread.sleep(100);while(clip.isRunning()) {Thread.sleep(100);}
    }
    catch(Exception e){e.printStackTrace(System.err);}
  }
}
