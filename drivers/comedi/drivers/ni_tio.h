<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Header file क्रम NI general purpose counter support code (ni_tio.c)
 *
 * COMEDI - Linux Control and Measurement Device Interface
 */

#अगर_अघोषित _COMEDI_NI_TIO_H
#घोषणा _COMEDI_NI_TIO_H

#समावेश "../comedidev.h"

क्रमागत ni_gpct_रेजिस्टर अणु
	NITIO_G0_AUTO_INC,
	NITIO_G1_AUTO_INC,
	NITIO_G2_AUTO_INC,
	NITIO_G3_AUTO_INC,
	NITIO_G0_CMD,
	NITIO_G1_CMD,
	NITIO_G2_CMD,
	NITIO_G3_CMD,
	NITIO_G0_HW_SAVE,
	NITIO_G1_HW_SAVE,
	NITIO_G2_HW_SAVE,
	NITIO_G3_HW_SAVE,
	NITIO_G0_SW_SAVE,
	NITIO_G1_SW_SAVE,
	NITIO_G2_SW_SAVE,
	NITIO_G3_SW_SAVE,
	NITIO_G0_MODE,
	NITIO_G1_MODE,
	NITIO_G2_MODE,
	NITIO_G3_MODE,
	NITIO_G0_LOADA,
	NITIO_G1_LOADA,
	NITIO_G2_LOADA,
	NITIO_G3_LOADA,
	NITIO_G0_LOADB,
	NITIO_G1_LOADB,
	NITIO_G2_LOADB,
	NITIO_G3_LOADB,
	NITIO_G0_INPUT_SEL,
	NITIO_G1_INPUT_SEL,
	NITIO_G2_INPUT_SEL,
	NITIO_G3_INPUT_SEL,
	NITIO_G0_CNT_MODE,
	NITIO_G1_CNT_MODE,
	NITIO_G2_CNT_MODE,
	NITIO_G3_CNT_MODE,
	NITIO_G0_GATE2,
	NITIO_G1_GATE2,
	NITIO_G2_GATE2,
	NITIO_G3_GATE2,
	NITIO_G01_STATUS,
	NITIO_G23_STATUS,
	NITIO_G01_RESET,
	NITIO_G23_RESET,
	NITIO_G01_STATUS1,
	NITIO_G23_STATUS1,
	NITIO_G01_STATUS2,
	NITIO_G23_STATUS2,
	NITIO_G0_DMA_CFG,
	NITIO_G1_DMA_CFG,
	NITIO_G2_DMA_CFG,
	NITIO_G3_DMA_CFG,
	NITIO_G0_DMA_STATUS,
	NITIO_G1_DMA_STATUS,
	NITIO_G2_DMA_STATUS,
	NITIO_G3_DMA_STATUS,
	NITIO_G0_ABZ,
	NITIO_G1_ABZ,
	NITIO_G0_INT_ACK,
	NITIO_G1_INT_ACK,
	NITIO_G2_INT_ACK,
	NITIO_G3_INT_ACK,
	NITIO_G0_STATUS,
	NITIO_G1_STATUS,
	NITIO_G2_STATUS,
	NITIO_G3_STATUS,
	NITIO_G0_INT_ENA,
	NITIO_G1_INT_ENA,
	NITIO_G2_INT_ENA,
	NITIO_G3_INT_ENA,
	NITIO_NUM_REGS,
पूर्ण;

क्रमागत ni_gpct_variant अणु
	ni_gpct_variant_e_series,
	ni_gpct_variant_m_series,
	ni_gpct_variant_660x
पूर्ण;

काष्ठा ni_gpct अणु
	काष्ठा ni_gpct_device *counter_dev;
	अचिन्हित पूर्णांक counter_index;
	अचिन्हित पूर्णांक chip_index;
	u64 घड़ी_period_ps;	/* घड़ी period in picoseconds */
	काष्ठा mite_channel *mite_chan;
	spinlock_t lock;	/* protects 'mite_chan' */
पूर्ण;

काष्ठा ni_gpct_device अणु
	काष्ठा comedi_device *dev;
	व्योम (*ग_लिखो)(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक value,
		      क्रमागत ni_gpct_रेजिस्टर);
	अचिन्हित पूर्णांक (*पढ़ो)(काष्ठा ni_gpct *counter, क्रमागत ni_gpct_रेजिस्टर);
	क्रमागत ni_gpct_variant variant;
	काष्ठा ni_gpct *counters;
	अचिन्हित पूर्णांक num_counters;
	अचिन्हित पूर्णांक num_chips;
	अचिन्हित पूर्णांक (*regs)[NITIO_NUM_REGS]; /* [num_chips][NITIO_NUM_REGS] */
	spinlock_t regs_lock;		/* protects 'regs' */
	स्थिर काष्ठा ni_route_tables *routing_tables; /* link to routes */
पूर्ण;

काष्ठा ni_gpct_device *
ni_gpct_device_स्थिरruct(काष्ठा comedi_device *dev,
			 व्योम (*ग_लिखो)(काष्ठा ni_gpct *counter,
				       अचिन्हित पूर्णांक value,
				       क्रमागत ni_gpct_रेजिस्टर),
			 अचिन्हित पूर्णांक (*पढ़ो)(काष्ठा ni_gpct *counter,
					      क्रमागत ni_gpct_रेजिस्टर),
			 क्रमागत ni_gpct_variant,
			 अचिन्हित पूर्णांक num_counters,
			 अचिन्हित पूर्णांक counters_per_chip,
			 स्थिर काष्ठा ni_route_tables *routing_tables);
व्योम ni_gpct_device_destroy(काष्ठा ni_gpct_device *counter_dev);
व्योम ni_tio_init_counter(काष्ठा ni_gpct *counter);
पूर्णांक ni_tio_insn_पढ़ो(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		     काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
पूर्णांक ni_tio_insn_config(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
पूर्णांक ni_tio_insn_ग_लिखो(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		      काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
पूर्णांक ni_tio_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s);
पूर्णांक ni_tio_cmdtest(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		   काष्ठा comedi_cmd *cmd);
पूर्णांक ni_tio_cancel(काष्ठा ni_gpct *counter);
व्योम ni_tio_handle_पूर्णांकerrupt(काष्ठा ni_gpct *counter,
			     काष्ठा comedi_subdevice *s);
व्योम ni_tio_set_mite_channel(काष्ठा ni_gpct *counter,
			     काष्ठा mite_channel *mite_chan);
व्योम ni_tio_acknowledge(काष्ठा ni_gpct *counter);

/*
 * Retrieves the रेजिस्टर value of the current source of the output selector क्रम
 * the given destination.
 *
 * If the terminal क्रम the destination is not alपढ़ोy configured as an output,
 * this function वापसs -EINVAL as error.
 *
 * Return: the रेजिस्टर value of the destination output selector;
 *         -EINVAL अगर terminal is not configured क्रम output.
 */
पूर्णांक ni_tio_get_routing(काष्ठा ni_gpct_device *counter_dev,
		       अचिन्हित पूर्णांक destination);

/*
 * Sets the रेजिस्टर value of the selector MUX क्रम the given destination.
 * @counter_dev:Poपूर्णांकer to general counter device.
 * @destination:Device-global identअगरier of route destination.
 * @रेजिस्टर_value:
 *		The first several bits of this value should store the desired
 *		value to ग_लिखो to the रेजिस्टर.  All other bits are क्रम
 *		transmitting inक्रमmation that modअगरy the mode of the particular
 *		destination/gate.  These mode bits might include a bitwise or of
 *		CR_INVERT and CR_EDGE.  Note that the calling function should
 *		have alपढ़ोy validated the correctness of this value.
 */
पूर्णांक ni_tio_set_routing(काष्ठा ni_gpct_device *counter_dev,
		       अचिन्हित पूर्णांक destination, अचिन्हित पूर्णांक रेजिस्टर_value);

/*
 * Sets the given destination MUX to its शेष value or disable it.
 *
 * Return: 0 अगर successful; -EINVAL अगर terminal is unknown.
 */
पूर्णांक ni_tio_unset_routing(काष्ठा ni_gpct_device *counter_dev,
			 अचिन्हित पूर्णांक destination);

#पूर्ण_अगर /* _COMEDI_NI_TIO_H */
