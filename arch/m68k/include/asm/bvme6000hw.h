<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_BVME6000HW_H_
#घोषणा _M68K_BVME6000HW_H_

#समावेश <यंत्र/irq.h>

/*
 * PIT काष्ठाure
 */

#घोषणा BVME_PIT_BASE	0xffa00000

प्रकार काष्ठा अणु
	अचिन्हित अक्षर
	pad_a[3], pgcr,
	pad_b[3], psrr,
	pad_c[3], paddr,
	pad_d[3], pbddr,
	pad_e[3], pcddr,
	pad_f[3], pivr,
	pad_g[3], pacr,
	pad_h[3], pbcr,
	pad_i[3], padr,
	pad_j[3], pbdr,
	pad_k[3], paar,
	pad_l[3], pbar,
	pad_m[3], pcdr,
	pad_n[3], psr,
	pad_o[3], res1,
	pad_p[3], res2,
	pad_q[3], tcr,
	pad_r[3], tivr,
	pad_s[3], res3,
	pad_t[3], cprh,
	pad_u[3], cprm,
	pad_v[3], cprl,
	pad_w[3], res4,
	pad_x[3], crh,
	pad_y[3], crm,
	pad_z[3], crl,
	pad_A[3], tsr,
	pad_B[3], res5;
पूर्ण PitRegs_t, *PitRegsPtr;

#घोषणा bvmepit   ((*(अस्थिर PitRegsPtr)(BVME_PIT_BASE)))

#घोषणा BVME_RTC_BASE	0xff900000

प्रकार काष्ठा अणु
	अचिन्हित अक्षर
	pad_a[3], msr,
	pad_b[3], t0cr_rपंचांगr,
	pad_c[3], t1cr_omr,
	pad_d[3], pfr_icr0,
	pad_e[3], irr_icr1,
	pad_f[3], bcd_tenms,
	pad_g[3], bcd_sec,
	pad_h[3], bcd_min,
	pad_i[3], bcd_hr,
	pad_j[3], bcd_करोm,
	pad_k[3], bcd_mth,
	pad_l[3], bcd_year,
	pad_m[3], bcd_ujcc,
	pad_n[3], bcd_hjcc,
	pad_o[3], bcd_करोw,
	pad_p[3], t0lsb,
	pad_q[3], t0msb,
	pad_r[3], t1lsb,
	pad_s[3], t1msb,
	pad_t[3], cmp_sec,
	pad_u[3], cmp_min,
	pad_v[3], cmp_hr,
	pad_w[3], cmp_करोm,
	pad_x[3], cmp_mth,
	pad_y[3], cmp_करोw,
	pad_z[3], sav_sec,
	pad_A[3], sav_min,
	pad_B[3], sav_hr,
	pad_C[3], sav_करोm,
	pad_D[3], sav_mth,
	pad_E[3], ram,
	pad_F[3], test;
पूर्ण RtcRegs_t, *RtcPtr_t;


#घोषणा BVME_I596_BASE	0xff100000

#घोषणा BVME_ETHIRQ_REG	0xff20000b

#घोषणा BVME_LOCAL_IRQ_STAT  0xff20000f

#घोषणा BVME_ETHERR          0x02
#घोषणा BVME_ABORT_STATUS    0x08

#घोषणा BVME_NCR53C710_BASE	0xff000000

#घोषणा BVME_SCC_A_ADDR	0xffb0000b
#घोषणा BVME_SCC_B_ADDR	0xffb00003
#घोषणा BVME_SCC_RTxC	7372800

#घोषणा BVME_CONFIG_REG	0xff500003

#घोषणा config_reg_ptr	(अस्थिर अचिन्हित अक्षर *)BVME_CONFIG_REG

#घोषणा BVME_CONFIG_SW1	0x08
#घोषणा BVME_CONFIG_SW2	0x04
#घोषणा BVME_CONFIG_SW3	0x02
#घोषणा BVME_CONFIG_SW4	0x01


#घोषणा BVME_IRQ_TYPE_PRIO	0

#घोषणा BVME_IRQ_PRN		(IRQ_USER+20)
#घोषणा BVME_IRQ_TIMER		(IRQ_USER+25)
#घोषणा BVME_IRQ_I596		IRQ_AUTO_2
#घोषणा BVME_IRQ_SCSI		IRQ_AUTO_3
#घोषणा BVME_IRQ_RTC		IRQ_AUTO_6
#घोषणा BVME_IRQ_ABORT		IRQ_AUTO_7

/* SCC पूर्णांकerrupts */
#घोषणा BVME_IRQ_SCC_BASE		IRQ_USER
#घोषणा BVME_IRQ_SCCB_TX		IRQ_USER
#घोषणा BVME_IRQ_SCCB_STAT		(IRQ_USER+2)
#घोषणा BVME_IRQ_SCCB_RX		(IRQ_USER+4)
#घोषणा BVME_IRQ_SCCB_SPCOND		(IRQ_USER+6)
#घोषणा BVME_IRQ_SCCA_TX		(IRQ_USER+8)
#घोषणा BVME_IRQ_SCCA_STAT		(IRQ_USER+10)
#घोषणा BVME_IRQ_SCCA_RX		(IRQ_USER+12)
#घोषणा BVME_IRQ_SCCA_SPCOND		(IRQ_USER+14)

/* Address control रेजिस्टरs */

#घोषणा BVME_ACR_A32VBA		0xff400003
#घोषणा BVME_ACR_A32MSK		0xff410003
#घोषणा BVME_ACR_A24VBA		0xff420003
#घोषणा BVME_ACR_A24MSK		0xff430003
#घोषणा BVME_ACR_A16VBA		0xff440003
#घोषणा BVME_ACR_A32LBA		0xff450003
#घोषणा BVME_ACR_A24LBA		0xff460003
#घोषणा BVME_ACR_ADDRCTL	0xff470003

#घोषणा bvme_acr_a32vba		*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_A32VBA
#घोषणा bvme_acr_a32msk		*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_A32MSK
#घोषणा bvme_acr_a24vba		*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_A24VBA
#घोषणा bvme_acr_a24msk		*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_A24MSK
#घोषणा bvme_acr_a16vba		*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_A16VBA
#घोषणा bvme_acr_a32lba		*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_A32LBA
#घोषणा bvme_acr_a24lba		*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_A24LBA
#घोषणा bvme_acr_addrctl	*(अस्थिर अचिन्हित अक्षर *)BVME_ACR_ADDRCTL

#पूर्ण_अगर
