/*
* Some theoric considerations:
*   - The ADC is a 12-bit sucessive approximation register (SAR) ADC. 
*   - Multiplexed input channels (8)
*   - 200khz max conversion rate
*   - Operation modes: Burst mode, single conversion mode, continuous conversion mode
*   - Interrupt generation
*   - 0v to 3.3v input range
*/

/*
* Remember Nyquist theorem: f >= 2 * f_max
* f_max = 10kHz
* f = 20kHz
* Calculate the frequency of the ADC -> 20kHz
* fadc = 20kHz*65=1.3MHz
* 
*
* 
*/

