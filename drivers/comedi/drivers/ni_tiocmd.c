<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Command support क्रम NI general purpose counters
 *
 * Copyright (C) 2006 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

/*
 * Module: ni_tiocmd
 * Description: National Instruments general purpose counters command support
 * Author: J.P. Mellor <jpmellor@rose-hulman.edu>,
 *         Herman.Bruyninckx@mech.kuleuven.ac.be,
 *         Wim.Meeussen@mech.kuleuven.ac.be,
 *         Klaas.Gadeyne@mech.kuleuven.ac.be,
 *         Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Updated: Fri, 11 Apr 2008 12:32:35 +0100
 * Status: works
 *
 * This module is not used directly by end-users.  Rather, it
 * is used by other drivers (क्रम example ni_660x and ni_pcimio)
 * to provide command support क्रम NI's general purpose counters.
 * It was originally split out of ni_tio.c to stop the 'ni_tio'
 * module depending on the 'mite' module.
 *
 * References:
 * DAQ 660x Register-Level Programmer Manual  (NI 370505A-01)
 * DAQ 6601/6602 User Manual (NI 322137B-01)
 * 340934b.pdf  DAQ-STC reference manual
 *
 * TODO: Support use of both banks X and Y
 */

#समावेश <linux/module.h>
#समावेश "ni_tio_internal.h"
#समावेश "mite.h"
#समावेश "ni_routes.h"

अटल व्योम ni_tio_configure_dma(काष्ठा ni_gpct *counter,
				 bool enable, bool पढ़ो)
अणु
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक bits;

	mask = GI_READ_ACKS_IRQ | GI_WRITE_ACKS_IRQ;
	bits = 0;

	अगर (enable) अणु
		अगर (पढ़ो)
			bits |= GI_READ_ACKS_IRQ;
		अन्यथा
			bits |= GI_WRITE_ACKS_IRQ;
	पूर्ण
	ni_tio_set_bits(counter, NITIO_INPUT_SEL_REG(cidx), mask, bits);

	चयन (counter_dev->variant) अणु
	हाल ni_gpct_variant_e_series:
		अवरोध;
	हाल ni_gpct_variant_m_series:
	हाल ni_gpct_variant_660x:
		mask = GI_DMA_ENABLE | GI_DMA_INT_ENA | GI_DMA_WRITE;
		bits = 0;

		अगर (enable)
			bits |= GI_DMA_ENABLE | GI_DMA_INT_ENA;
		अगर (!पढ़ो)
			bits |= GI_DMA_WRITE;
		ni_tio_set_bits(counter, NITIO_DMA_CFG_REG(cidx), mask, bits);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ni_tio_input_पूर्णांकtrig(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	spin_lock_irqsave(&counter->lock, flags);
	अगर (counter->mite_chan)
		mite_dma_arm(counter->mite_chan);
	अन्यथा
		ret = -EIO;
	spin_unlock_irqrestore(&counter->lock, flags);
	अगर (ret < 0)
		वापस ret;
	ret = ni_tio_arm(counter, true, NI_GPCT_ARM_IMMEDIATE);
	s->async->पूर्णांकtrig = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक ni_tio_input_cmd(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	काष्ठा ni_gpct_device *counter_dev = counter->counter_dev;
	स्थिर काष्ठा ni_route_tables *routing_tables =
		counter_dev->routing_tables;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	पूर्णांक ret = 0;

	/* ग_लिखो alloc the entire buffer */
	comedi_buf_ग_लिखो_alloc(s, async->pपुनः_स्मृति_bufsz);
	counter->mite_chan->dir = COMEDI_INPUT;
	चयन (counter_dev->variant) अणु
	हाल ni_gpct_variant_m_series:
	हाल ni_gpct_variant_660x:
		mite_prep_dma(counter->mite_chan, 32, 32);
		अवरोध;
	हाल ni_gpct_variant_e_series:
		mite_prep_dma(counter->mite_chan, 16, 32);
		अवरोध;
	पूर्ण
	ni_tio_set_bits(counter, NITIO_CMD_REG(cidx), GI_SAVE_TRACE, 0);
	ni_tio_configure_dma(counter, true, true);

	अगर (cmd->start_src == TRIG_INT) अणु
		async->पूर्णांकtrig = &ni_tio_input_पूर्णांकtrig;
	पूर्ण अन्यथा अणु	/* TRIG_NOW || TRIG_EXT || TRIG_OTHER */
		async->पूर्णांकtrig = शून्य;
		mite_dma_arm(counter->mite_chan);

		अगर (cmd->start_src == TRIG_NOW)
			ret = ni_tio_arm(counter, true, NI_GPCT_ARM_IMMEDIATE);
		अन्यथा अगर (cmd->start_src == TRIG_EXT) अणु
			पूर्णांक reg = CR_CHAN(cmd->start_arg);

			अगर (reg >= NI_NAMES_BASE) अणु
				/* using a device-global name. lookup reg */
				reg = ni_get_reg_value(reg,
						       NI_CtrArmStartTrigger(cidx),
						       routing_tables);
				/* mark this as a raw रेजिस्टर value */
				reg |= NI_GPCT_HW_ARM;
			पूर्ण
			ret = ni_tio_arm(counter, true, reg);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ni_tio_output_cmd(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;

	dev_err(counter->counter_dev->dev->class_dev,
		"output commands not yet implemented.\n");
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ni_tio_cmd_setup(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	काष्ठा ni_gpct *counter = s->निजी;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	स्थिर काष्ठा ni_route_tables *routing_tables =
		counter->counter_dev->routing_tables;
	पूर्णांक set_gate_source = 0;
	अचिन्हित पूर्णांक gate_source;
	पूर्णांक retval = 0;

	अगर (cmd->scan_begin_src == TRIG_EXT) अणु
		set_gate_source = 1;
		gate_source = cmd->scan_begin_arg;
	पूर्ण अन्यथा अगर (cmd->convert_src == TRIG_EXT) अणु
		set_gate_source = 1;
		gate_source = cmd->convert_arg;
	पूर्ण
	अगर (set_gate_source) अणु
		अगर (CR_CHAN(gate_source) >= NI_NAMES_BASE) अणु
			/* Lookup and use the real रेजिस्टर values */
			पूर्णांक reg = ni_get_reg_value(CR_CHAN(gate_source),
						   NI_CtrGate(cidx),
						   routing_tables);
			अगर (reg < 0)
				वापस -EINVAL;
			retval = ni_tio_set_gate_src_raw(counter, 0, reg);
		पूर्ण अन्यथा अणु
			/*
			 * This function must be used separately since it करोes
			 * not expect real रेजिस्टर values and attempts to
			 * convert these to real रेजिस्टर values.
			 */
			retval = ni_tio_set_gate_src(counter, 0, gate_source);
		पूर्ण
	पूर्ण
	अगर (cmd->flags & CMDF_WAKE_EOS) अणु
		ni_tio_set_bits(counter, NITIO_INT_ENA_REG(cidx),
				GI_GATE_INTERRUPT_ENABLE(cidx),
				GI_GATE_INTERRUPT_ENABLE(cidx));
	पूर्ण
	वापस retval;
पूर्ण

पूर्णांक ni_tio_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&counter->lock, flags);
	अगर (!counter->mite_chan) अणु
		dev_err(counter->counter_dev->dev->class_dev,
			"commands only supported with DMA.  ");
		dev_err(counter->counter_dev->dev->class_dev,
			"Interrupt-driven commands not yet implemented.\n");
		retval = -EIO;
	पूर्ण अन्यथा अणु
		retval = ni_tio_cmd_setup(s);
		अगर (retval == 0) अणु
			अगर (cmd->flags & CMDF_WRITE)
				retval = ni_tio_output_cmd(s);
			अन्यथा
				retval = ni_tio_input_cmd(s);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&counter->lock, flags);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_cmd);

पूर्णांक ni_tio_cmdtest(काष्ठा comedi_device *dev,
		   काष्ठा comedi_subdevice *s,
		   काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	स्थिर काष्ठा ni_route_tables *routing_tables =
		counter->counter_dev->routing_tables;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक sources;

	/* Step 1 : check अगर triggers are trivially valid */

	sources = TRIG_NOW | TRIG_INT | TRIG_OTHER;
	अगर (ni_tio_counting_mode_रेजिस्टरs_present(counter->counter_dev))
		sources |= TRIG_EXT;
	err |= comedi_check_trigger_src(&cmd->start_src, sources);

	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_EXT | TRIG_OTHER);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_NOW | TRIG_EXT | TRIG_OTHER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->convert_src != TRIG_NOW && cmd->scan_begin_src != TRIG_FOLLOW)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
	हाल TRIG_INT:
	हाल TRIG_OTHER:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		/* start_arg is the start_trigger passed to ni_tio_arm() */
		/*
		 * This should be करोne, but we करोn't yet know the actual
		 * रेजिस्टर values.  These should be tested and then करोcumented
		 * in the ni_route_values/ni_*.csv files, with indication of
		 * who/when/which/how these were tested.
		 * When at least a e/m/660x series have been tested, this code
		 * should be uncommented:
		 *
		 * err |= ni_check_trigger_arg(CR_CHAN(cmd->start_arg),
		 *			    NI_CtrArmStartTrigger(cidx),
		 *			    routing_tables);
		 */
		अवरोध;
	पूर्ण

	/*
	 * It seems that convention is to allow either scan_begin_arg or
	 * convert_arg to specअगरy the Gate source, with scan_begin_arg taking
	 * precedence.
	 */
	अगर (cmd->scan_begin_src != TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	अन्यथा
		err |= ni_check_trigger_arg(CR_CHAN(cmd->scan_begin_arg),
					    NI_CtrGate(cidx), routing_tables);

	अगर (cmd->convert_src != TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	अन्यथा
		err |= ni_check_trigger_arg(CR_CHAN(cmd->convert_arg),
					    NI_CtrGate(cidx), routing_tables);

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_cmdtest);

पूर्णांक ni_tio_cancel(काष्ठा ni_gpct *counter)
अणु
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित दीर्घ flags;

	ni_tio_arm(counter, false, 0);
	spin_lock_irqsave(&counter->lock, flags);
	अगर (counter->mite_chan)
		mite_dma_disarm(counter->mite_chan);
	spin_unlock_irqrestore(&counter->lock, flags);
	ni_tio_configure_dma(counter, false, false);

	ni_tio_set_bits(counter, NITIO_INT_ENA_REG(cidx),
			GI_GATE_INTERRUPT_ENABLE(cidx), 0x0);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_cancel);

अटल पूर्णांक should_ack_gate(काष्ठा ni_gpct *counter)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	चयन (counter->counter_dev->variant) अणु
	हाल ni_gpct_variant_m_series:
	हाल ni_gpct_variant_660x:
		/*
		 * not sure अगर 660x really supports gate पूर्णांकerrupts
		 * (the bits are not listed in रेजिस्टर-level manual)
		 */
		वापस 1;
	हाल ni_gpct_variant_e_series:
		/*
		 * During buffered input counter operation क्रम e-series,
		 * the gate पूर्णांकerrupt is acked स्वतःmatically by the dma
		 * controller, due to the Gi_Read/Write_Acknowledges_IRQ
		 * bits in the input select रेजिस्टर.
		 */
		spin_lock_irqsave(&counter->lock, flags);
		अणु
			अगर (!counter->mite_chan ||
			    counter->mite_chan->dir != COMEDI_INPUT ||
			    (mite_करोne(counter->mite_chan))) अणु
				retval = 1;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&counter->lock, flags);
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम ni_tio_acknowledge_and_confirm(काष्ठा ni_gpct *counter,
					   पूर्णांक *gate_error,
					   पूर्णांक *tc_error,
					   पूर्णांक *perm_stale_data)
अणु
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	स्थिर अचिन्हित लघु gxx_status = ni_tio_पढ़ो(counter,
						NITIO_SHARED_STATUS_REG(cidx));
	स्थिर अचिन्हित लघु gi_status = ni_tio_पढ़ो(counter,
						NITIO_STATUS_REG(cidx));
	अचिन्हित पूर्णांक ack = 0;

	अगर (gate_error)
		*gate_error = 0;
	अगर (tc_error)
		*tc_error = 0;
	अगर (perm_stale_data)
		*perm_stale_data = 0;

	अगर (gxx_status & GI_GATE_ERROR(cidx)) अणु
		ack |= GI_GATE_ERROR_CONFIRM(cidx);
		अगर (gate_error) अणु
			/*
			 * 660x करोn't support स्वतःmatic acknowledgment
			 * of gate पूर्णांकerrupt via dma पढ़ो/ग_लिखो
			 * and report bogus gate errors
			 */
			अगर (counter->counter_dev->variant !=
			    ni_gpct_variant_660x)
				*gate_error = 1;
		पूर्ण
	पूर्ण
	अगर (gxx_status & GI_TC_ERROR(cidx)) अणु
		ack |= GI_TC_ERROR_CONFIRM(cidx);
		अगर (tc_error)
			*tc_error = 1;
	पूर्ण
	अगर (gi_status & GI_TC)
		ack |= GI_TC_INTERRUPT_ACK;
	अगर (gi_status & GI_GATE_INTERRUPT) अणु
		अगर (should_ack_gate(counter))
			ack |= GI_GATE_INTERRUPT_ACK;
	पूर्ण
	अगर (ack)
		ni_tio_ग_लिखो(counter, ack, NITIO_INT_ACK_REG(cidx));
	अगर (ni_tio_get_soft_copy(counter, NITIO_MODE_REG(cidx)) &
	    GI_LOADING_ON_GATE) अणु
		अगर (ni_tio_पढ़ो(counter, NITIO_STATUS2_REG(cidx)) &
		    GI_PERMANENT_STALE(cidx)) अणु
			dev_info(counter->counter_dev->dev->class_dev,
				 "%s: Gi_Permanent_Stale_Data detected.\n",
				 __func__);
			अगर (perm_stale_data)
				*perm_stale_data = 1;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ni_tio_acknowledge(काष्ठा ni_gpct *counter)
अणु
	ni_tio_acknowledge_and_confirm(counter, शून्य, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_acknowledge);

व्योम ni_tio_handle_पूर्णांकerrupt(काष्ठा ni_gpct *counter,
			     काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक cidx = counter->counter_index;
	अचिन्हित दीर्घ flags;
	पूर्णांक gate_error;
	पूर्णांक tc_error;
	पूर्णांक perm_stale_data;

	ni_tio_acknowledge_and_confirm(counter, &gate_error, &tc_error,
				       &perm_stale_data);
	अगर (gate_error) अणु
		dev_notice(counter->counter_dev->dev->class_dev,
			   "%s: Gi_Gate_Error detected.\n", __func__);
		s->async->events |= COMEDI_CB_OVERFLOW;
	पूर्ण
	अगर (perm_stale_data)
		s->async->events |= COMEDI_CB_ERROR;
	चयन (counter->counter_dev->variant) अणु
	हाल ni_gpct_variant_m_series:
	हाल ni_gpct_variant_660x:
		अगर (ni_tio_पढ़ो(counter, NITIO_DMA_STATUS_REG(cidx)) &
		    GI_DRQ_ERROR) अणु
			dev_notice(counter->counter_dev->dev->class_dev,
				   "%s: Gi_DRQ_Error detected.\n", __func__);
			s->async->events |= COMEDI_CB_OVERFLOW;
		पूर्ण
		अवरोध;
	हाल ni_gpct_variant_e_series:
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&counter->lock, flags);
	अगर (counter->mite_chan)
		mite_ack_linkc(counter->mite_chan, s, true);
	spin_unlock_irqrestore(&counter->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_handle_पूर्णांकerrupt);

व्योम ni_tio_set_mite_channel(काष्ठा ni_gpct *counter,
			     काष्ठा mite_channel *mite_chan)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&counter->lock, flags);
	counter->mite_chan = mite_chan;
	spin_unlock_irqrestore(&counter->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ni_tio_set_mite_channel);

अटल पूर्णांक __init ni_tiocmd_init_module(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(ni_tiocmd_init_module);

अटल व्योम __निकास ni_tiocmd_cleanup_module(व्योम)
अणु
पूर्ण
module_निकास(ni_tiocmd_cleanup_module);

MODULE_AUTHOR("Comedi <comedi@comedi.org>");
MODULE_DESCRIPTION("Comedi command support for NI general-purpose counters");
MODULE_LICENSE("GPL");
