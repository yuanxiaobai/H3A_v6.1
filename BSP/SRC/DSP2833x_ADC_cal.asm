;; TI File $Revision: 1.9 $
;; Checkin $Date: 2014/10/23 02:21:03 $
;;###########################################################################
;;
;; FILE:    ADC_cal.asm
;;
;; TITLE:   2833x Boot Rom ADC Cal routine.
;;
;; Functions:
;;
;;     _ADC_cal - Copies device specific calibration data into ADCREFSEL and ADCOFFTRIM registers 
;; Notes:
;;
;;###########################################################################
;; $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
;; $Release Date: August 4, 2009 $
;;###########################################################################

    .def _ADC_cal
	.asg "0x711C",   ADCREFSEL_LOC

;-----------------------------------------------
; _ADC_cal
;-----------------------------------------------
;-----------------------------------------------
; This is the ADC cal routine.This routine is programmed into 
; reserved memory by the factory. 0xAAAA and 0xBBBB are place- 
; holders for calibration data.  
;The actual values programmed by TI are device specific. 
;
; This function assumes that the clocks have been
; enabled to the ADC module.
;-----------------------------------------------

    .sect ".adc_cal"

_ADC_cal
    MOVW  DP,   #ADCREFSEL_LOC >> 6
    MOV   @28,  #0xAAAA            ; actual value may not be 0xAAAA
    MOV   @29,  #0xBBBB             ; actual value may not be 0xBBBB
    LRETR
;eof ----------
