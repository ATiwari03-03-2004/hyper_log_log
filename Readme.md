# HyperLogLog (HLL)

HLL a probabilistic data structure which is used to evaluate the unique elements of a set (cardinality). It's widely used in real production environment to estimate number of unique users using an application at a time, because classic algorithm and data structure to do so are even though simple to implement but are not feasible in terms of time and space complexity, wheras HLL is exactly suited for this kind of situation. A thing to take note is that even though it's a probablistic estimator it was observed to have a error of approx. 2%, which is great considering the sheer number of people using these applications (like Google, Meta, etc).<br>
<b>Note:</b> Here, In this implementation HLL evaluates the number of unqiue names/strings that are provided through input.<br>

### HLL Implementation detail:-
Here, let's say i provided a name "anshuman" as an input<br>

"anshuman" is converted into a 64-bit hash using MURMUR Hash 64-A algorithm<br>

"anshuman" -> [MURMUR Hash 64-A] -> 8492496817851202345 (64-bit hash) <br>

Now, the real operation is performed on the binary representation of the 64-bit hash, for simplicity I will be using a simple random binary number instead of binary representation of the 64-bit hash.<br>

Some, basic info before jumping ahead:<br>
<b>b :</b> represents the intital bits of the binary 64-bit hash (which is utilized as index of the registers/buckets)<br>
<b>m :</b> represents the number/size of registers/buckets (m = 2<sup>b</sup>)<br>

Now, let's say binary representation of 64-bit hash was <b>0010011010</b><br>
for this case let's assume b = 3 and thus m = 2<sup>b</sup> = 2<sup>3</sup> = 8<br>

Therefore, first b bits of the the binary number is used as index of registers
registers = [0, 0, 0, 0, 0, 0, 0, 0] (eight registers will be used)<br>
In binary representation first b = 3 bits are 001 in decimal its 1, meaning that registers[1]. Now, for the remaining bits from binary representation, we find the position of first 1 from MSB bit i.e. here 0011010, position = 3<br>
Now, we simply make registers[i] = max(registers[i], position)<br>
registers = [0, 3, 0, 0, 0, 0, 0, 0]<br>

This procedure occurs for every input string provided and register gets automatically updated depending on position of 1 in the reamaing 64 - b (bits).<br>

Now, comes the real deal, which is evaluating the cardinality, to do this we use a very simple formula<br>
cardinality_hll = $\frac{hll\_const \cdot m^{2}}{\sum_{i=0}^{m-1} 2^{-\text{registers}[i]}}$<br>

<b><u>Note:</u></b><br>
<b>hll_const :</b> is evaluated using following switch case block<br>
```cpp
switch (m) {
    case 16:
        hll_const = 0.673;
        break;
    case 32:
        hll_const = 0.697;
        break;
    case 64:
        hll_const = 0.709;
        break;
    default:
        hll_const = 0.7213 / (1.0 + (1.079 / m));
        break;
}
```
<b>cardinality_hll :</b> In general case forula to evaluate works very precisely but there are some problems that must be handled in case of the provided input set being very small there is a likelihood of an overshoot in cardinality and thus we use small range correction and similary if the input set is very large we must also perform large range correction which is as given below<br>
```cpp
// This method is stated in the HLL paper
double pow_2_64 = 18446744073709551616.0;
double neg_pow_2_64 = -18446744073709551616.0;
if (cardinality_temp <= 2.5 * m) { // small range correction -> by shifting to linear counting
    size_t zeroCnt = 0;
    for (size_t i = 0; i < m; i++) {
        if (registers[i] == 0) {
            zeroCnt++;
        }
    }
    if (zeroCnt != 0) {
        cardinality_temp = m * std::log((double)m / zeroCnt);
    }
} else if (cardinality_temp > (1.0 / 30.0) * pow_2_64) { // large range correction
    cardinality_temp = neg_pow_2_64 * log(1.0 - (cardinality_temp / pow_2_64));
}
```
As for the hashing used in HLL any hashing algorithm works as long as it has randomness and uniqueness preferably Murmurhash variants, SHA-1, etc. These are simple non cryptographic algos for hashes and preety simple to implement though I think you can use cryptographic ones but I believe it would be an overkill.<br>

I tried to go through the simple implementation part of HLL. For more details read through the offical paper and Wikipedia pages to get a better understanding<br>


