import java.math.BigInteger;
import java.util.Random;
import java.util.Scanner;

public class RSA {

    private static Random rand = new Random();
    private final static int keyBitLength = 160;

    private static BigInteger[] genKeys()
    {
        BigInteger publicKey;
        BigInteger privateKey;
        BigInteger N;
        BigInteger p = BigInteger.probablePrime(keyBitLength, rand);
        BigInteger q = BigInteger.probablePrime(keyBitLength, rand);
        while(p.equals(q))
            p = BigInteger.probablePrime(keyBitLength, rand);

        BigInteger n = p.multiply(q);
        p = p.subtract(BigInteger.valueOf(1));
        q = q.subtract(BigInteger.valueOf(1));
        N = p.multiply(q);
        for(publicKey = BigInteger.valueOf(17); !publicKey.gcd(N).equals(BigInteger.ONE); publicKey = publicKey.add(BigInteger.ONE));
        privateKey = publicKey.modInverse(N);
        System.out.println("priv: " + privateKey + "\n" + "pub: " + publicKey + "\n" + "mod: " + N);
        return new BigInteger[]{privateKey, publicKey, n};
    }

    private static BigInteger slowPow(BigInteger base, BigInteger exp, BigInteger mod)
    {
        BigInteger w = BigInteger.ONE;
        for(int a = exp.bitLength() - 1; a >= 0; --a)
        {
            if(exp.testBit(a))
                w = w.multiply(w.multiply(base)).mod(mod);
            else
                w = w.multiply(w).mod(mod);
        }
        return w;
    }

    private static BigInteger slowEncrypt(BigInteger number, BigInteger publicKey, BigInteger n)
    {
        return slowPow(number, publicKey, n);
    }

    private static BigInteger slowDecrypt(BigInteger cipher, BigInteger privateKey, BigInteger n)
    {
        return slowPow(cipher, privateKey, n);
    }

    private static BigInteger encrypt(BigInteger number, BigInteger publicKey, BigInteger n)
    {
        return number.modPow(publicKey, n);
    }

    private static BigInteger decrypt(BigInteger cipher, BigInteger privateKey, BigInteger n)
    {
        return cipher.modPow(privateKey, n);
    }

    private static BigInteger sign(BigInteger number, BigInteger privateKey, BigInteger n)
    {
        int hash = number.toString().hashCode();
        return BigInteger.valueOf(hash).modPow(privateKey, n);
    }

    private static boolean verify(BigInteger message, BigInteger sign, BigInteger publicKey, BigInteger n)
    {
        int temp = sign.modPow(publicKey, n).intValue();
        int hash = message.toString().hashCode();
        return temp == hash;
    }

    public static void main(String[] args){
        BigInteger encrypted = BigInteger.valueOf(Integer.parseInt(args[0]));
        BigInteger keys[];
        System.out.println("To encrypt: " + encrypted);
        keys = genKeys();
        encrypted = slowEncrypt(encrypted, keys[1], keys[2]);
        System.out.println("Encrypted Message: " + encrypted);
        encrypted = slowDecrypt(encrypted, keys[0], keys[2]);
        System.out.println("Decrypted Message: " + encrypted);
    }
}
