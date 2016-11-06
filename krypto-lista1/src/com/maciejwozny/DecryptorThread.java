package com.maciejwozny;

import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.binary.Hex;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

/**
 * Created by maciek on 26.10.16.
 */

public class DecryptorThread extends Thread
{
    public final String[] hex = Main.hex;
    String suffixKey = Main.suffixKey;
    static final String encrypted = Main.encrypted;
    private IvParameterSpec iv;
    private Cipher cipher;

    static boolean isASCII1(String s)
    {
        for (int i = 0; i < s.length(); i++)
            if (s.charAt(i) > 127)
                return false;
        return true;
    }

    static boolean isASCII(String s)
    {
        int nonASCII = 0;
        int maxBlednych = 5;
        int length = Integer.min(maxBlednych, s.length());
        for (int i = 0; i < length; i++) {
            if (s.charAt(i) > 127)
                ++nonASCII;
        }
        for (int i = length; i < s.length(); ++i)
        {
            if (s.charAt(i) > 127)
                ++nonASCII;
            if (nonASCII > maxBlednych)
                return false;
        }
        return true;
    }

    void init() throws Exception
    {
        String initVector = Main.initVector;
        byte[] initVectorByte = Hex.decodeHex(initVector.toCharArray());
        iv = new IvParameterSpec(Hex.decodeHex(initVector.toCharArray()));
        cipher = Cipher.getInstance("AES/CBC/PKCS5PADDING");
    }

//    @Override
    public void runZad1()
    {
        try {
            init();
            String ID = Main.getChar();
            suffixKey = ID + suffixKey;
            for (String first : hex){
                for (String second : hex){
                    for (String third : hex){
                        for (String fourth : hex) {
                            for (String fifth : hex) {
                                for(String sixth : hex) {
                                    for(String seventh : hex) {
                                        try {
                                            String key = first + second + third + fourth + fifth + sixth + seventh + suffixKey;
                                            SecretKeySpec secretKey = new SecretKeySpec(Hex.decodeHex(key.toCharArray()), "AES");
                                            cipher.init(Cipher.DECRYPT_MODE, secretKey, iv);

                                            byte[] original = cipher.doFinal(Base64.decodeBase64(encrypted));

                                            String result = new String(original);

                                            if (isASCII(result)) {
                                                System.out.println(key + " " + result);
                                                Main.addResult(key + " " + result);
                                            }
                                        } catch (Exception e) {
                                        }
                                    }
                                }
                            }
                        }
                    }
                    System.out.println("ID = " + ID + ", first char = " + first + second);
                }
            }
        }
        catch (Exception e)
        {
            System.err.println(e.getMessage() + "\n" +e.getLocalizedMessage());
        }

    }

    @Override
    public void run()
    {
        try {
            init();
            String ID = Main.getChar();
            suffixKey = ID + suffixKey;
            for (String first : hex){
                for (String second : hex){
                    for (String third : hex){
                        for (String fourth : hex) {
                            for (String fifth : hex) {
                                for(String sixth : hex) {
                                    for(String seventh : hex) {
                                        for (String eight : hex) {
                                            try {
                                                String key = first + second + third + fourth + fifth + sixth + seventh + eight + suffixKey;
                                                SecretKeySpec secretKey = new SecretKeySpec(Hex.decodeHex(key.toCharArray()), "AES");
                                                cipher.init(Cipher.DECRYPT_MODE, secretKey, iv);

                                                byte[] original = cipher.doFinal(Base64.decodeBase64(encrypted));

                                                String result = new String(original);

                                                if (isASCII(result)) {
                                                    System.out.println(key + " " + result);
                                                    Main.addResult(key + " " + result);
                                                }
                                            } catch (Exception e) {
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    System.out.println("ID = " + ID + ", first char = " + first + second);
                }
            }
        }
        catch (Exception e)
        {
            System.err.println(e.getMessage() + "\n" +e.getLocalizedMessage());
        }

    }
}