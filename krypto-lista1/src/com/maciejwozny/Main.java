package com.maciejwozny;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.binary.Hex;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;



public class Main {
    private final String zad1Key = "3a2da4920b76bf1952cf38b9f6f4e5da73b7ed6d9b3dfb18f5a1a0811713b747 ";
    private final String zad1Result = "Zamieszanie wokol wpisu Krystyny Jandy, w ktorym poskarzyla sie, ze nie rozpoznal jej sprzedawca w sklepie, uderzylo rykoszetem w dzialalnosc artystyczna tej wybitnej aktorki.";

//    public static final String[] hex = { "f" , "e" , "d", "c", "b", "a", "9", "8", "7", "6", "5", "4", "3", "2", "1", "0"};
    public static final String[] hex = { "0" , "1" , "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
//    public static final String[] hex = { "0" , /*"1" ,*/ "2", "3", /*"4", "5", "6", "7", */"8", "9", "a", /*"b", "c", "d", */"e", "f"};

    static int id = 0;

//    static final String key = "8a223e09 5fd90f91e13e0a4c596e5d3f27edff4f5ca5dad41ecd4148ed1549aa"; // 128 bit key
//    static final String suffixKey = "5fd90f91e13e0a4c596e5d3f27edff4f5ca5dad41ecd4148ed1549aa";
//    static final String initVector = "7b81af7530218d47d454cee5207309e8"; // 16 bytes IV
//    static final String encrypted = "06d3sLGP7l4Q6RBnB/cIQgU2r/O7rGerDiNpBQzW1Z3ZFV6XQSdva9tQ/60Y7x03Qg4abc3Oxqx11v+UNREGk43ynhyY/FMGxAEreHVdOcjPWPav9cJQI9Wvv/c3CI4LApPcnbXDzJBYdTmMJLUEYw==";

    static final String suffixKey = "f380c5d89341cc33fbcb2fff4ba997d02807eed4103a5961679466a";
    static final String initVector = "e9413fe6e0c9789c1ac75316555e7a6c"; // 16 bytes IV
    static final String encrypted = "tE29qTCMCDQ9kJ+5s6z26k0k2Nbpuizi2zQR6bqgvkwsBbxTI4YFhXu3X8C+6PHCiESSF7jtSETbDlfbR7NTebhpxyM1Y/A6qzVUv0SJPprhvo6HEH6vnqVgrUqhv5RRxEs1gCfTTkIzKsORHBOqHMoodSTITJ0XeaYEgsvuftifI9V0PAYinxfnS6Jy7Bj/qyc5vUbH2HaN8/X3IXm4aA==";

    private static IvParameterSpec iv;
    private static Cipher cipher;

    static synchronized final String getChar()
    {
        return hex[id++];
    }

    static List<String> resultList = new ArrayList<>();
    static synchronized void addResult(String txt)
    {
        resultList.add(txt);
    }

    static void init() throws Exception
    {
        byte[] initVectorByte = Hex.decodeHex(initVector.toCharArray());
        iv = new IvParameterSpec(Hex.decodeHex(initVector.toCharArray()));
        cipher = Cipher.getInstance("AES/CBC/PKCS5PADDING");
    }

    public static void main(String[] args) throws Exception {
        init();

        String timeStampStart = new SimpleDateFormat("HH:mm:ss").format(Calendar.getInstance().getTime());
        System.out.println("START: " + timeStampStart);

        List<DecryptorThread> threadList = new ArrayList<>();
        for (Object i : hex)
        {
            threadList.add(new DecryptorThread());
        }

        for (Thread thread : threadList)
        {
            thread.start();
        }

        for (Thread thread : threadList)
        {
            thread.join();
            System.out.println("DONE");
        }
        String timeStampEnd = new SimpleDateFormat("HH:mm:ss").format(Calendar.getInstance().getTime());
        System.out.println("DONE: " + timeStampStart + " - " + timeStampEnd);

        for (String result : resultList)
        {
            System.out.println(result);
        }

//
//        System.out.println(decrypt(key, initVector,
//                encrypt(key, iv,
//                        "Ala ma kota. Kot ma, ale... to jednak ona go posiada. Jednakże gdy przeczytamy to ponownie to...")));


    }

//=================================================================================

    private static boolean isASCII(String s)
    {
        for (int i = 0; i < s.length(); i++)
            if (s.charAt(i) > 127)
                return false;
        return true;
    }

    public static String encrypt(String key, IvParameterSpec iv, String value) {
        try {
            SecretKeySpec secretKey = new SecretKeySpec(Hex.decodeHex(key.toCharArray()), "AES");

            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5PADDING");
            cipher.init(Cipher.ENCRYPT_MODE, secretKey, iv);

            byte[] encrypted = cipher.doFinal(value.getBytes());
            System.out.println("encrypted string: "
                    + Base64.encodeBase64String(encrypted));

            return Base64.encodeBase64String(encrypted);
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        return null;
    }

    public static String decrypt(String key, String initVector, String encrypted) {
        try {
            IvParameterSpec iv = new IvParameterSpec(Hex.decodeHex(initVector.toCharArray()));
            SecretKeySpec secretKey = new SecretKeySpec(Hex.decodeHex(key.toCharArray()), "AES");

            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, secretKey, iv);

            byte[] original = cipher.doFinal(Base64.decodeBase64(encrypted));

            return new String(original);
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        return null;
    }



}
