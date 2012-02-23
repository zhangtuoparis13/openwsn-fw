/**
\brief Register definitions for the Texas Instruments CC2420 radio chip.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012.
*/

#ifndef __CC2420_H
#define __CC2420_H

//=========================== spi flags =======================================

#define CC2420_FLAG_READ          0x40
#define CC2420_FLAG_WRITE         0x00

#define CC2420_FLAG_RAM           0x80
#define CC2420_FLAG_REG           0x00

//=========================== status byte =====================================

typedef struct {
   uint8_t res1:1;
   uint8_t xosc16m_stable:1;
   uint8_t tx_underflow:1;
   uint8_t enc_busy:1;
   uint8_t tx_active:1;
   uint8_t lock:1;
   uint8_t rssi_valid:1;
   uint8_t res2:1;
} cc2420_status_t;

//=========================== strobes =========================================

#define CC2420_SNOP               0x00 // [S  ] No Operation
#define CC2420_SXOSCON            0x01 // [S  ] Turn on the crystal oscillator
#define CC2420_STXCAL             0x02 // [S  ] Enable and calibrate frequency synthesizer for TX
#define CC2420_SRXON              0x03 // [S  ] Enable RX
#define CC2420_STXON              0x04 // [S  ] Enable TX after calibration (if not already performed)
#define CC2420_STXONCCA           0x05 // [S  ] If CCA indicates a clear channel, Enable calibration, then TX
#define CC2420_SRFOFF             0x06 // [S  ] Disable RX/TX and frequency synthesizer
#define CC2420_SXOSCOFF           0x07 // [S  ] Turn off the crystal oscillator and RF
#define CC2420_SFLUSHRX           0x08 // [S  ] Flush the RX FIFO buffer and reset the demodulator
#define CC2420_SFLUSHTX           0x09 // [S  ] Flush the TX FIFO buffer
#define CC2420_SACK               0x0a // [S  ] Send acknowledge frame, with pending field cleared
#define CC2420_SACKPEND           0x0b // [S  ] Send acknowledge frame, with pending field set
#define CC2420_SRXDEC             0x0c // [S  ] Start RXFIFO in-line decryption / authentication
#define CC2420_STXENC             0x0d // [S  ] Start TXFIFO in-line encryption / authentication
#define CC2420_SAES               0x0e // [S  ] AES Stand alone encryption strobe

//=========================== registers =======================================

/// [R/W] Main Control Register
#define CC2420_MAIN_ADDR          0x10
typedef struct {
   uint16_t XOSC16M_BYPASS:1;
   uint16_t reserved:10;
   uint16_t FS_RESETn:1;
   uint16_t MOD_RESETn:1;
   uint16_t DEMOD_RESETn:1;
   uint16_t ENC_RESETn:1;
   uint16_t RESETn:1;
} cc2420_MAIN_reg_t;

/// [R/W] Modem Control Register 0
#define CC2420_MDMCTRL0_ADDR      0x11
typedef struct {
   uint16_t PREAMBLE_LENGTH:4;
   uint16_t AUTOACK:1;
   uint16_t AUTOCRC:1;
   uint16_t CCA_MODE:2;
   uint16_t CCA_HYST:3;
   uint16_t ADR_DECODE:1;
   uint16_t PAN_COORDINATOR:1;
   uint16_t RESERVED_FRAME_MODE:1;
   uint16_t reserved:2;
} cc2420_MDMCTRL0_reg_t;

/// [R/W] Modem Control Register 1
#define CC2420_MDMCTRL1_ADDR      0x12
typedef struct {
   uint16_t RX_MODE:2;
   uint16_t TX_MODE:2;
   uint16_t MODULATION_MODE:1;
   uint16_t DEMOD_AVG_MODE:1;
   uint16_t CORR_THR:5;
   uint16_t reserved:5;
} cc2420_MDMCTRL1_reg_t;

// [R/W] RSSI and CCA Status and Control register
#define CC2420_RSSI_ADDR          0x13
typedef struct {
   uint16_t RSSI_VAL:8;
   uint16_t CCR_THR:8;
} cc2420_RSSI_reg_t;

/// [R/W] Synchronisation word control register
#define CC2420_SYNCWORD_ADDR      0x14
typedef struct {
   uint16_t SYNCWORD:16;
} cc2420_SYNCWORD_reg_t;

/// [R/W] Transmit Control Register
#define CC2420_TXCTRL_ADDR        0x15
typedef struct {
   uint16_t PA_LEVEL:5;
   uint16_t reserved:1;
   uint16_t PA_CURRENT:3;
   uint16_t TXMIX_CURRENT:2;
   uint16_t TXMIX_CAP_ARRAY:2;
   uint16_t TX_TURNAROUND:1;
   uint16_t TXMIXBUF_CUR:2;
} cc2420_TXCTRL_reg_t;

/// [R/W] Receive Control Register 0
#define CC2420_RXCTRL0_ADDR       0x16
typedef struct {
   uint16_t LOW_LNA_CURRENT:2;
   uint16_t MED_LNA_CURRENT:2;
   uint16_t HIGH_LNA_CURRENT:2;
   uint16_t LOW_LNA_GAIN:2;
   uint16_t MED_LNA_GAIN:2;
   uint16_t HIGH_LNA_GAIN:2;
   uint16_t RXMIXBUF_CUR:2;
   uint16_t reserved:2;
} cc2420_RXCTRL0_reg_t;

/// [R/W] Receive Control Register 1
#define CC2420_RXCTRL1_ADDR       0x17
typedef struct {
   uint16_t RXMIX_CURRENT:2;
   uint16_t RXMIX_VCM:2;
   uint16_t RXMIX_TAIL:2;
   uint16_t LNA_CAP_ARRAY:2;
   uint16_t MED_HGM:1;
   uint16_t HIGH_HGM:1;
   uint16_t MED_LOWGAIN:1;
   uint16_t LOW_LOWGAIN:1;
   uint16_t RXBPF_MIDCUR:1;
   uint16_t RXBPF_LOCUR:1;
   uint16_t reserved:2;
} cc2420_RXCTRL1_reg_t;

/// [R/W] Frequency Synthesizer Control and Status Register
#define CC2420_FSCTRL_ADDR        0x18
typedef struct {
   uint16_t poipoi:1;
} cc2420_FSCTRL_reg_t;

/// [R/W] Security Control Register 0
#define CC2420_SECCTRL0_ADDR      0x19
typedef struct {
   uint16_t poipoi:1;
} cc2420_SECCTRL0_reg_t;

/// [R/W] Security Control Register 1
#define CC2420_SECCTRL1_ADDR      0x1a
typedef struct {
   uint16_t poipoi:1;
} cc2420_SECCTRL1_reg_t;

/// [R/W] Battery Monitor Control and Status Register
#define CC2420_BATTMON_ADDR       0x1b
typedef struct {
   uint16_t poipoi:1;
} cc2420_BATTMON_reg_t;

/// [R/W] Input / Output Control Register 0
#define CC2420_IOCFG0_ADDR        0x1c
typedef struct {
   uint16_t poipoi:1;
} cc2420_IOCFG0_reg_t;

/// [R/W] Input / Output Control Register 1
#define CC2420_IOCFG1_ADDR        0x1d
typedef struct {
   uint16_t poipoi:1;
} cc2420_IOCFG1_reg_t;

/// [R/W] Manufacturer ID, Low 16 bits
#define CC2420_MANFIDL_ADDR       0x1e
typedef struct {
   uint16_t mandif:12;
   uint16_t partnum:4;
} cc2420_MANFIDL_reg_t;

/// [R/W] Manufacturer ID, High 16 bits
#define CC2420_MANFIDH_ADDR       0x1f
typedef struct {
   uint16_t poipoi:1;
} cc2420_MANFIDH_reg_t;

/// [R/W] Finite State Machine Time Constants
#define CC2420_FSMTC_ADDR         0x20
typedef struct {
   uint16_t poipoi:1;
} cc2420_FSMTC_reg_t;

/// [R/W] Manual signal AND override register
#define CC2420_MANAND_ADDR        0x21
typedef struct {
   uint16_t poipoi:1;
} cc2420_MANAND_reg_t;

/// [R/W] Manual signal OR override register
#define CC2420_MANOR_ADDR         0x22
typedef struct {
   uint16_t poipoi:1;
} cc2420_MANOR_reg_t;

/// [R/W] AGC Control Register
#define CC2420_AGCCTRL_ADDR       0x23
typedef struct {
   uint16_t poipoi:1;
} cc2420_AGCCTRL_reg_t;

/// [R/W] AGC Test Register 0
#define CC2420_AGCTST0_ADDR       0x24
typedef struct {
   uint16_t poipoi:1;
} cc2420_AGCTST0_reg_t;

/// [R/W] AGC Test Register 1
#define CC2420_AGCTST1_ADDR       0x25
typedef struct {
   uint16_t poipoi:1;
} cc2420_AGCTST1_reg_t;

/// [R/W] AGC Test Register 2
#define CC2420_AGCTST2_ADDR       0x26
typedef struct {
   uint16_t poipoi:1;
} cc2420_AGCTST2_reg_t;

/// [R/W] Frequency Synthesizer Test Register 0
#define CC2420_FSTST0_ADDR        0x27
typedef struct {
   uint16_t poipoi:1;
} cc2420_FSTST0_reg_t;

/// [R/W] Frequency Synthesizer Test Register 1
#define CC2420_FSTST1_ADDR        0x28
typedef struct {
   uint16_t poipoi:1;
} cc2420_FSTST1_reg_t;

/// [R/W] Frequency Synthesizer Test Register 2
#define CC2420_FSTST2_ADDR        0x29
typedef struct {
   uint16_t poipoi:1;
} cc2420_FSTST2_reg_t;

/// [R/W] Frequency Synthesizer Test Register 3
#define CC2420_FSTST3_ADDR        0x2a
typedef struct {
   uint16_t poipoi:1;
} cc2420_FSTST3_reg_t;

/// [R/W] Receiver Bandpass Filter Test Register
#define CC2420_RXBPFTST_ADDR      0x2b
typedef struct {
   uint16_t poipoi:1;
} cc2420_RXBPFTST_reg_t;

/// [R  ] Finite State Machine State Status Register
#define CC2420_FSMSTATE_ADDR      0x2c
typedef struct {
   uint16_t poipoi:1;
} cc2420_FSMSTATE_reg_t;

/// [R/W] ADC Test Register
#define CC2420_ADCTST_ADDR        0x2c
typedef struct {
   uint16_t poipoi:1;
} cc2420_ADCTST_reg_t;

/// [R/W] DAC Test Register
#define CC2420_DACTST_ADDR        0x2e
typedef struct {
   uint16_t poipoi:1;
} cc2420_DACTST_reg_t;

/// [R/W] Top Level Test Register
#define CC2420_TOPTST_ADDR        0x2f
typedef struct {
   uint16_t poipoi:1;
} cc2420_TOPTST_reg_t;

//=========================== buffer ==========================================

/// [  W] Transmit FIFO Byte Register
#define CC2420_TXFIFO_ADDR        0x3e

/// [R/W] Receiver FIFO Byte Register
#define CC2420_RXFIFO_ADDR        0x3f

#endif