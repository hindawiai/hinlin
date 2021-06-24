<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Header file क्रम NI general purpose counter support code (ni_tio.c and
 * ni_tiocmd.c)
 *
 * COMEDI - Linux Control and Measurement Device Interface
 */

#अगर_अघोषित _COMEDI_NI_TIO_INTERNAL_H
#घोषणा _COMEDI_NI_TIO_INTERNAL_H

#समावेश "ni_tio.h"

#घोषणा NITIO_AUTO_INC_REG(x)		(NITIO_G0_AUTO_INC + (x))
#घोषणा GI_AUTO_INC_MASK		0xff
#घोषणा NITIO_CMD_REG(x)		(NITIO_G0_CMD + (x))
#घोषणा GI_ARM				BIT(0)
#घोषणा GI_SAVE_TRACE			BIT(1)
#घोषणा GI_LOAD				BIT(2)
#घोषणा GI_DISARM			BIT(4)
#घोषणा GI_CNT_सूची(x)			(((x) & 0x3) << 5)
#घोषणा GI_CNT_सूची_MASK			GI_CNT_सूची(3)
#घोषणा GI_WRITE_SWITCH			BIT(7)
#घोषणा GI_SYNC_GATE			BIT(8)
#घोषणा GI_LITTLE_BIG_ENDIAN		BIT(9)
#घोषणा GI_BANK_SWITCH_START		BIT(10)
#घोषणा GI_BANK_SWITCH_MODE		BIT(11)
#घोषणा GI_BANK_SWITCH_ENABLE		BIT(12)
#घोषणा GI_ARM_COPY			BIT(13)
#घोषणा GI_SAVE_TRACE_COPY		BIT(14)
#घोषणा GI_DISARM_COPY			BIT(15)
#घोषणा NITIO_HW_SAVE_REG(x)		(NITIO_G0_HW_SAVE + (x))
#घोषणा NITIO_SW_SAVE_REG(x)		(NITIO_G0_SW_SAVE + (x))
#घोषणा NITIO_MODE_REG(x)		(NITIO_G0_MODE + (x))
#घोषणा GI_GATING_MODE(x)		(((x) & 0x3) << 0)
#घोषणा GI_GATING_DISABLED		GI_GATING_MODE(0)
#घोषणा GI_LEVEL_GATING			GI_GATING_MODE(1)
#घोषणा GI_RISING_EDGE_GATING		GI_GATING_MODE(2)
#घोषणा GI_FALLING_EDGE_GATING		GI_GATING_MODE(3)
#घोषणा GI_GATING_MODE_MASK		GI_GATING_MODE(3)
#घोषणा GI_GATE_ON_BOTH_EDGES		BIT(2)
#घोषणा GI_EDGE_GATE_MODE(x)		(((x) & 0x3) << 3)
#घोषणा GI_EDGE_GATE_STARTS_STOPS	GI_EDGE_GATE_MODE(0)
#घोषणा GI_EDGE_GATE_STOPS_STARTS	GI_EDGE_GATE_MODE(1)
#घोषणा GI_EDGE_GATE_STARTS		GI_EDGE_GATE_MODE(2)
#घोषणा GI_EDGE_GATE_NO_STARTS_OR_STOPS	GI_EDGE_GATE_MODE(3)
#घोषणा GI_EDGE_GATE_MODE_MASK		GI_EDGE_GATE_MODE(3)
#घोषणा GI_STOP_MODE(x)			(((x) & 0x3) << 5)
#घोषणा GI_STOP_ON_GATE			GI_STOP_MODE(0)
#घोषणा GI_STOP_ON_GATE_OR_TC		GI_STOP_MODE(1)
#घोषणा GI_STOP_ON_GATE_OR_SECOND_TC	GI_STOP_MODE(2)
#घोषणा GI_STOP_MODE_MASK		GI_STOP_MODE(3)
#घोषणा GI_LOAD_SRC_SEL			BIT(7)
#घोषणा GI_OUTPUT_MODE(x)		(((x) & 0x3) << 8)
#घोषणा GI_OUTPUT_TC_PULSE		GI_OUTPUT_MODE(1)
#घोषणा GI_OUTPUT_TC_TOGGLE		GI_OUTPUT_MODE(2)
#घोषणा GI_OUTPUT_TC_OR_GATE_TOGGLE	GI_OUTPUT_MODE(3)
#घोषणा GI_OUTPUT_MODE_MASK		GI_OUTPUT_MODE(3)
#घोषणा GI_COUNTING_ONCE(x)		(((x) & 0x3) << 10)
#घोषणा GI_NO_HARDWARE_DISARM		GI_COUNTING_ONCE(0)
#घोषणा GI_DISARM_AT_TC			GI_COUNTING_ONCE(1)
#घोषणा GI_DISARM_AT_GATE		GI_COUNTING_ONCE(2)
#घोषणा GI_DISARM_AT_TC_OR_GATE		GI_COUNTING_ONCE(3)
#घोषणा GI_COUNTING_ONCE_MASK		GI_COUNTING_ONCE(3)
#घोषणा GI_LOADING_ON_TC		BIT(12)
#घोषणा GI_GATE_POL_INVERT		BIT(13)
#घोषणा GI_LOADING_ON_GATE		BIT(14)
#घोषणा GI_RELOAD_SRC_SWITCHING		BIT(15)
#घोषणा NITIO_LOADA_REG(x)		(NITIO_G0_LOADA + (x))
#घोषणा NITIO_LOADB_REG(x)		(NITIO_G0_LOADB + (x))
#घोषणा NITIO_INPUT_SEL_REG(x)		(NITIO_G0_INPUT_SEL + (x))
#घोषणा GI_READ_ACKS_IRQ		BIT(0)
#घोषणा GI_WRITE_ACKS_IRQ		BIT(1)
#घोषणा GI_BITS_TO_SRC(x)		(((x) >> 2) & 0x1f)
#घोषणा GI_SRC_SEL(x)			(((x) & 0x1f) << 2)
#घोषणा GI_SRC_SEL_MASK			GI_SRC_SEL(0x1f)
#घोषणा GI_BITS_TO_GATE(x)		(((x) >> 7) & 0x1f)
#घोषणा GI_GATE_SEL(x)			(((x) & 0x1f) << 7)
#घोषणा GI_GATE_SEL_MASK		GI_GATE_SEL(0x1f)
#घोषणा GI_GATE_SEL_LOAD_SRC		BIT(12)
#घोषणा GI_OR_GATE			BIT(13)
#घोषणा GI_OUTPUT_POL_INVERT		BIT(14)
#घोषणा GI_SRC_POL_INVERT		BIT(15)
#घोषणा NITIO_CNT_MODE_REG(x)		(NITIO_G0_CNT_MODE + (x))
#घोषणा GI_CNT_MODE(x)			(((x) & 0x7) << 0)
#घोषणा GI_CNT_MODE_NORMAL		GI_CNT_MODE(0)
#घोषणा GI_CNT_MODE_QUADX1		GI_CNT_MODE(1)
#घोषणा GI_CNT_MODE_QUADX2		GI_CNT_MODE(2)
#घोषणा GI_CNT_MODE_QUADX4		GI_CNT_MODE(3)
#घोषणा GI_CNT_MODE_TWO_PULSE		GI_CNT_MODE(4)
#घोषणा GI_CNT_MODE_SYNC_SRC		GI_CNT_MODE(6)
#घोषणा GI_CNT_MODE_MASK		GI_CNT_MODE(7)
#घोषणा GI_INDEX_MODE			BIT(4)
#घोषणा GI_INDEX_PHASE(x)		(((x) & 0x3) << 5)
#घोषणा GI_INDEX_PHASE_MASK		GI_INDEX_PHASE(3)
#घोषणा GI_HW_ARM_ENA			BIT(7)
#घोषणा GI_HW_ARM_SEL(x)		((x) << 8)
#घोषणा GI_660X_HW_ARM_SEL_MASK		GI_HW_ARM_SEL(0x7)
#घोषणा GI_M_HW_ARM_SEL_MASK		GI_HW_ARM_SEL(0x1f)
#घोषणा GI_660X_PRESCALE_X8		BIT(12)
#घोषणा GI_M_PRESCALE_X8		BIT(13)
#घोषणा GI_660X_ALT_SYNC		BIT(13)
#घोषणा GI_M_ALT_SYNC			BIT(14)
#घोषणा GI_660X_PRESCALE_X2		BIT(14)
#घोषणा GI_M_PRESCALE_X2		BIT(15)
#घोषणा NITIO_GATE2_REG(x)		(NITIO_G0_GATE2 + (x))
#घोषणा GI_GATE2_MODE			BIT(0)
#घोषणा GI_BITS_TO_GATE2(x)		(((x) >> 7) & 0x1f)
#घोषणा GI_GATE2_SEL(x)			(((x) & 0x1f) << 7)
#घोषणा GI_GATE2_SEL_MASK		GI_GATE2_SEL(0x1f)
#घोषणा GI_GATE2_POL_INVERT		BIT(13)
#घोषणा GI_GATE2_SUBSEL			BIT(14)
#घोषणा GI_SRC_SUBSEL			BIT(15)
#घोषणा NITIO_SHARED_STATUS_REG(x)	(NITIO_G01_STATUS + ((x) / 2))
#घोषणा GI_SAVE(x)			(((x) % 2) ? BIT(1) : BIT(0))
#घोषणा GI_COUNTING(x)			(((x) % 2) ? BIT(3) : BIT(2))
#घोषणा GI_NEXT_LOAD_SRC(x)		(((x) % 2) ? BIT(5) : BIT(4))
#घोषणा GI_STALE_DATA(x)		(((x) % 2) ? BIT(7) : BIT(6))
#घोषणा GI_ARMED(x)			(((x) % 2) ? BIT(9) : BIT(8))
#घोषणा GI_NO_LOAD_BETWEEN_GATES(x)	(((x) % 2) ? BIT(11) : BIT(10))
#घोषणा GI_TC_ERROR(x)			(((x) % 2) ? BIT(13) : BIT(12))
#घोषणा GI_GATE_ERROR(x)		(((x) % 2) ? BIT(15) : BIT(14))
#घोषणा NITIO_RESET_REG(x)		(NITIO_G01_RESET + ((x) / 2))
#घोषणा GI_RESET(x)			BIT(2 + ((x) % 2))
#घोषणा NITIO_STATUS1_REG(x)		(NITIO_G01_STATUS1 + ((x) / 2))
#घोषणा NITIO_STATUS2_REG(x)		(NITIO_G01_STATUS2 + ((x) / 2))
#घोषणा GI_OUTPUT(x)			(((x) % 2) ? BIT(1) : BIT(0))
#घोषणा GI_HW_SAVE(x)			(((x) % 2) ? BIT(13) : BIT(12))
#घोषणा GI_PERMANENT_STALE(x)		(((x) % 2) ? BIT(15) : BIT(14))
#घोषणा NITIO_DMA_CFG_REG(x)		(NITIO_G0_DMA_CFG + (x))
#घोषणा GI_DMA_ENABLE			BIT(0)
#घोषणा GI_DMA_WRITE			BIT(1)
#घोषणा GI_DMA_INT_ENA			BIT(2)
#घोषणा GI_DMA_RESET			BIT(3)
#घोषणा GI_DMA_BANKSW_ERROR		BIT(4)
#घोषणा NITIO_DMA_STATUS_REG(x)		(NITIO_G0_DMA_STATUS + (x))
#घोषणा GI_DMA_READBANK			BIT(13)
#घोषणा GI_DRQ_ERROR			BIT(14)
#घोषणा GI_DRQ_STATUS			BIT(15)
#घोषणा NITIO_ABZ_REG(x)		(NITIO_G0_ABZ + (x))
#घोषणा NITIO_INT_ACK_REG(x)		(NITIO_G0_INT_ACK + (x))
#घोषणा GI_GATE_ERROR_CONFIRM(x)	(((x) % 2) ? BIT(1) : BIT(5))
#घोषणा GI_TC_ERROR_CONFIRM(x)		(((x) % 2) ? BIT(2) : BIT(6))
#घोषणा GI_TC_INTERRUPT_ACK		BIT(14)
#घोषणा GI_GATE_INTERRUPT_ACK		BIT(15)
#घोषणा NITIO_STATUS_REG(x)		(NITIO_G0_STATUS + (x))
#घोषणा GI_GATE_INTERRUPT		BIT(2)
#घोषणा GI_TC				BIT(3)
#घोषणा GI_INTERRUPT			BIT(15)
#घोषणा NITIO_INT_ENA_REG(x)		(NITIO_G0_INT_ENA + (x))
#घोषणा GI_TC_INTERRUPT_ENABLE(x)	(((x) % 2) ? BIT(9) : BIT(6))
#घोषणा GI_GATE_INTERRUPT_ENABLE(x)	(((x) % 2) ? BIT(10) : BIT(8))

व्योम ni_tio_ग_लिखो(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक value,
		  क्रमागत ni_gpct_रेजिस्टर);
अचिन्हित पूर्णांक ni_tio_पढ़ो(काष्ठा ni_gpct *counter, क्रमागत ni_gpct_रेजिस्टर);

अटल अंतरभूत bool
ni_tio_counting_mode_रेजिस्टरs_present(स्थिर काष्ठा ni_gpct_device *counter_dev)
अणु
	/* m series and 660x variants have counting mode रेजिस्टरs */
	वापस counter_dev->variant != ni_gpct_variant_e_series;
पूर्ण

व्योम ni_tio_set_bits(काष्ठा ni_gpct *counter, क्रमागत ni_gpct_रेजिस्टर reg,
		     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value);
अचिन्हित पूर्णांक ni_tio_get_soft_copy(स्थिर काष्ठा ni_gpct *counter,
				  क्रमागत ni_gpct_रेजिस्टर reg);

पूर्णांक ni_tio_arm(काष्ठा ni_gpct *counter, bool arm, अचिन्हित पूर्णांक start_trigger);
पूर्णांक ni_tio_set_gate_src(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक gate,
			अचिन्हित पूर्णांक src);
पूर्णांक ni_tio_set_gate_src_raw(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक gate,
			    अचिन्हित पूर्णांक src);

#पूर्ण_अगर /* _COMEDI_NI_TIO_INTERNAL_H */
