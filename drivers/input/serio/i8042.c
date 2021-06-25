<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  i8042 keyboard and mouse controller driver क्रम Linux
 *
 *  Copyright (c) 1999-2004 Vojtech Pavlik
 */


#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/serपन.स>
#समावेश <linux/err.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i8042.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/property.h>

#समावेश <यंत्र/पन.स>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@suse.cz>");
MODULE_DESCRIPTION("i8042 keyboard and mouse controller driver");
MODULE_LICENSE("GPL");

अटल bool i8042_nokbd;
module_param_named(nokbd, i8042_nokbd, bool, 0);
MODULE_PARM_DESC(nokbd, "Do not probe or use KBD port.");

अटल bool i8042_noaux;
module_param_named(noaux, i8042_noaux, bool, 0);
MODULE_PARM_DESC(noaux, "Do not probe or use AUX (mouse) port.");

अटल bool i8042_nomux;
module_param_named(nomux, i8042_nomux, bool, 0);
MODULE_PARM_DESC(nomux, "Do not check whether an active multiplexing controller is present.");

अटल bool i8042_unlock;
module_param_named(unlock, i8042_unlock, bool, 0);
MODULE_PARM_DESC(unlock, "Ignore keyboard lock.");

क्रमागत i8042_controller_reset_mode अणु
	I8042_RESET_NEVER,
	I8042_RESET_ALWAYS,
	I8042_RESET_ON_S2RAM,
#घोषणा I8042_RESET_DEFAULT	I8042_RESET_ON_S2RAM
पूर्ण;
अटल क्रमागत i8042_controller_reset_mode i8042_reset = I8042_RESET_DEFAULT;
अटल पूर्णांक i8042_set_reset(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	क्रमागत i8042_controller_reset_mode *arg = kp->arg;
	पूर्णांक error;
	bool reset;

	अगर (val) अणु
		error = kstrtobool(val, &reset);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		reset = true;
	पूर्ण

	*arg = reset ? I8042_RESET_ALWAYS : I8042_RESET_NEVER;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_reset_param = अणु
	.flags = KERNEL_PARAM_OPS_FL_NOARG,
	.set = i8042_set_reset,
पूर्ण;
#घोषणा param_check_reset_param(name, p)	\
	__param_check(name, p, क्रमागत i8042_controller_reset_mode)
module_param_named(reset, i8042_reset, reset_param, 0);
MODULE_PARM_DESC(reset, "Reset controller on resume, cleanup or both");

अटल bool i8042_direct;
module_param_named(direct, i8042_direct, bool, 0);
MODULE_PARM_DESC(direct, "Put keyboard port into non-translated mode.");

अटल bool i8042_dumbkbd;
module_param_named(dumbkbd, i8042_dumbkbd, bool, 0);
MODULE_PARM_DESC(dumbkbd, "Pretend that controller can only read data from keyboard");

अटल bool i8042_noloop;
module_param_named(noloop, i8042_noloop, bool, 0);
MODULE_PARM_DESC(noloop, "Disable the AUX Loopback command while probing for the AUX port");

अटल bool i8042_noसमयout;
module_param_named(noसमयout, i8042_noसमयout, bool, 0);
MODULE_PARM_DESC(noसमयout, "Ignore timeouts signalled by i8042");

अटल bool i8042_kbdreset;
module_param_named(kbdreset, i8042_kbdreset, bool, 0);
MODULE_PARM_DESC(kbdreset, "Reset device connected to KBD port");

#अगर_घोषित CONFIG_X86
अटल bool i8042_dritek;
module_param_named(dritek, i8042_dritek, bool, 0);
MODULE_PARM_DESC(dritek, "Force enable the Dritek keyboard extension");
#पूर्ण_अगर

#अगर_घोषित CONFIG_PNP
अटल bool i8042_nopnp;
module_param_named(nopnp, i8042_nopnp, bool, 0);
MODULE_PARM_DESC(nopnp, "Do not use PNP to detect controller settings");
#पूर्ण_अगर

#घोषणा DEBUG
#अगर_घोषित DEBUG
अटल bool i8042_debug;
module_param_named(debug, i8042_debug, bool, 0600);
MODULE_PARM_DESC(debug, "Turn i8042 debugging mode on and off");

अटल bool i8042_unmask_kbd_data;
module_param_named(unmask_kbd_data, i8042_unmask_kbd_data, bool, 0600);
MODULE_PARM_DESC(unmask_kbd_data, "Unconditional enable (may reveal sensitive data) of normally sanitize-filtered kbd data traffic debug log [pre-condition: i8042.debug=1 enabled]");
#पूर्ण_अगर

अटल bool i8042_present;
अटल bool i8042_bypass_aux_irq_test;
अटल अक्षर i8042_kbd_firmware_id[128];
अटल अक्षर i8042_aux_firmware_id[128];
अटल काष्ठा fwnode_handle *i8042_kbd_fwnode;

#समावेश "i8042.h"

/*
 * i8042_lock protects serialization between i8042_command and
 * the पूर्णांकerrupt handler.
 */
अटल DEFINE_SPINLOCK(i8042_lock);

/*
 * Writers to AUX and KBD ports as well as users issuing i8042_command
 * directly should acquire i8042_mutex (by means of calling
 * i8042_lock_chip() and i8042_unlock_ship() helpers) to ensure that
 * they करो not disturb each other (unक्रमtunately in many i8042
 * implementations ग_लिखो to one of the ports will immediately पात
 * command that is being processed by another port).
 */
अटल DEFINE_MUTEX(i8042_mutex);

काष्ठा i8042_port अणु
	काष्ठा serio *serio;
	पूर्णांक irq;
	bool exists;
	bool driver_bound;
	चिन्हित अक्षर mux;
पूर्ण;

#घोषणा I8042_KBD_PORT_NO	0
#घोषणा I8042_AUX_PORT_NO	1
#घोषणा I8042_MUX_PORT_NO	2
#घोषणा I8042_NUM_PORTS		(I8042_NUM_MUX_PORTS + 2)

अटल काष्ठा i8042_port i8042_ports[I8042_NUM_PORTS];

अटल अचिन्हित अक्षर i8042_initial_ctr;
अटल अचिन्हित अक्षर i8042_ctr;
अटल bool i8042_mux_present;
अटल bool i8042_kbd_irq_रेजिस्टरed;
अटल bool i8042_aux_irq_रेजिस्टरed;
अटल अचिन्हित अक्षर i8042_suppress_kbd_ack;
अटल काष्ठा platक्रमm_device *i8042_platक्रमm_device;
अटल काष्ठा notअगरier_block i8042_kbd_bind_notअगरier_block;

अटल irqवापस_t i8042_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल bool (*i8042_platक्रमm_filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				     काष्ठा serio *serio);

व्योम i8042_lock_chip(व्योम)
अणु
	mutex_lock(&i8042_mutex);
पूर्ण
EXPORT_SYMBOL(i8042_lock_chip);

व्योम i8042_unlock_chip(व्योम)
अणु
	mutex_unlock(&i8042_mutex);
पूर्ण
EXPORT_SYMBOL(i8042_unlock_chip);

पूर्णांक i8042_install_filter(bool (*filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
					काष्ठा serio *serio))
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&i8042_lock, flags);

	अगर (i8042_platक्रमm_filter) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	i8042_platक्रमm_filter = filter;

out:
	spin_unlock_irqrestore(&i8042_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(i8042_install_filter);

पूर्णांक i8042_हटाओ_filter(bool (*filter)(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				       काष्ठा serio *port))
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&i8042_lock, flags);

	अगर (i8042_platक्रमm_filter != filter) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	i8042_platक्रमm_filter = शून्य;

out:
	spin_unlock_irqrestore(&i8042_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(i8042_हटाओ_filter);

/*
 * The i8042_रुको_पढ़ो() and i8042_रुको_ग_लिखो functions रुको क्रम the i8042 to
 * be पढ़ोy क्रम पढ़ोing values from it / writing values to it.
 * Called always with i8042_lock held.
 */

अटल पूर्णांक i8042_रुको_पढ़ो(व्योम)
अणु
	पूर्णांक i = 0;

	जबतक ((~i8042_पढ़ो_status() & I8042_STR_OBF) && (i < I8042_CTL_TIMEOUT)) अणु
		udelay(50);
		i++;
	पूर्ण
	वापस -(i == I8042_CTL_TIMEOUT);
पूर्ण

अटल पूर्णांक i8042_रुको_ग_लिखो(व्योम)
अणु
	पूर्णांक i = 0;

	जबतक ((i8042_पढ़ो_status() & I8042_STR_IBF) && (i < I8042_CTL_TIMEOUT)) अणु
		udelay(50);
		i++;
	पूर्ण
	वापस -(i == I8042_CTL_TIMEOUT);
पूर्ण

/*
 * i8042_flush() flushes all data that may be in the keyboard and mouse buffers
 * of the i8042 करोwn the toilet.
 */

अटल पूर्णांक i8042_flush(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर data, str;
	पूर्णांक count = 0;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&i8042_lock, flags);

	जबतक ((str = i8042_पढ़ो_status()) & I8042_STR_OBF) अणु
		अगर (count++ < I8042_BUFFER_SIZE) अणु
			udelay(50);
			data = i8042_पढ़ो_data();
			dbg("%02x <- i8042 (flush, %s)\n",
			    data, str & I8042_STR_AUXDATA ? "aux" : "kbd");
		पूर्ण अन्यथा अणु
			retval = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&i8042_lock, flags);

	वापस retval;
पूर्ण

/*
 * i8042_command() executes a command on the i8042. It also sends the input
 * parameter(s) of the commands to it, and receives the output value(s). The
 * parameters are to be stored in the param array, and the output is placed
 * पूर्णांकo the same array. The number of the parameters and output values is
 * encoded in bits 8-11 of the command number.
 */

अटल पूर्णांक __i8042_command(अचिन्हित अक्षर *param, पूर्णांक command)
अणु
	पूर्णांक i, error;

	अगर (i8042_noloop && command == I8042_CMD_AUX_LOOP)
		वापस -1;

	error = i8042_रुको_ग_लिखो();
	अगर (error)
		वापस error;

	dbg("%02x -> i8042 (command)\n", command & 0xff);
	i8042_ग_लिखो_command(command & 0xff);

	क्रम (i = 0; i < ((command >> 12) & 0xf); i++) अणु
		error = i8042_रुको_ग_लिखो();
		अगर (error) अणु
			dbg("     -- i8042 (wait write timeout)\n");
			वापस error;
		पूर्ण
		dbg("%02x -> i8042 (parameter)\n", param[i]);
		i8042_ग_लिखो_data(param[i]);
	पूर्ण

	क्रम (i = 0; i < ((command >> 8) & 0xf); i++) अणु
		error = i8042_रुको_पढ़ो();
		अगर (error) अणु
			dbg("     -- i8042 (wait read timeout)\n");
			वापस error;
		पूर्ण

		अगर (command == I8042_CMD_AUX_LOOP &&
		    !(i8042_पढ़ो_status() & I8042_STR_AUXDATA)) अणु
			dbg("     -- i8042 (auxerr)\n");
			वापस -1;
		पूर्ण

		param[i] = i8042_पढ़ो_data();
		dbg("%02x <- i8042 (return)\n", param[i]);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक i8042_command(अचिन्हित अक्षर *param, पूर्णांक command)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (!i8042_present)
		वापस -1;

	spin_lock_irqsave(&i8042_lock, flags);
	retval = __i8042_command(param, command);
	spin_unlock_irqrestore(&i8042_lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(i8042_command);

/*
 * i8042_kbd_ग_लिखो() sends a byte out through the keyboard पूर्णांकerface.
 */

अटल पूर्णांक i8042_kbd_ग_लिखो(काष्ठा serio *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&i8042_lock, flags);

	अगर (!(retval = i8042_रुको_ग_लिखो())) अणु
		dbg("%02x -> i8042 (kbd-data)\n", c);
		i8042_ग_लिखो_data(c);
	पूर्ण

	spin_unlock_irqrestore(&i8042_lock, flags);

	वापस retval;
पूर्ण

/*
 * i8042_aux_ग_लिखो() sends a byte out through the aux पूर्णांकerface.
 */

अटल पूर्णांक i8042_aux_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर c)
अणु
	काष्ठा i8042_port *port = serio->port_data;

	वापस i8042_command(&c, port->mux == -1 ?
					I8042_CMD_AUX_SEND :
					I8042_CMD_MUX_SEND + port->mux);
पूर्ण


/*
 * i8042_port_बंद attempts to clear AUX or KBD port state by disabling
 * and then re-enabling it.
 */

अटल व्योम i8042_port_बंद(काष्ठा serio *serio)
अणु
	पूर्णांक irq_bit;
	पूर्णांक disable_bit;
	स्थिर अक्षर *port_name;

	अगर (serio == i8042_ports[I8042_AUX_PORT_NO].serio) अणु
		irq_bit = I8042_CTR_AUXINT;
		disable_bit = I8042_CTR_AUXDIS;
		port_name = "AUX";
	पूर्ण अन्यथा अणु
		irq_bit = I8042_CTR_KBDINT;
		disable_bit = I8042_CTR_KBDDIS;
		port_name = "KBD";
	पूर्ण

	i8042_ctr &= ~irq_bit;
	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR))
		pr_warn("Can't write CTR while closing %s port\n", port_name);

	udelay(50);

	i8042_ctr &= ~disable_bit;
	i8042_ctr |= irq_bit;
	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR))
		pr_err("Can't reactivate %s port\n", port_name);

	/*
	 * See अगर there is any data appeared जबतक we were messing with
	 * port state.
	 */
	i8042_पूर्णांकerrupt(0, शून्य);
पूर्ण

/*
 * i8042_start() is called by serio core when port is about to finish
 * रेजिस्टरing. It will mark port as existing so i8042_पूर्णांकerrupt can
 * start sending data through it.
 */
अटल पूर्णांक i8042_start(काष्ठा serio *serio)
अणु
	काष्ठा i8042_port *port = serio->port_data;

	device_set_wakeup_capable(&serio->dev, true);

	/*
	 * On platक्रमms using suspend-to-idle, allow the keyboard to
	 * wake up the प्रणाली from sleep by enabling keyboard wakeups
	 * by शेष.  This is consistent with keyboard wakeup
	 * behavior on many platक्रमms using suspend-to-RAM (ACPI S3)
	 * by शेष.
	 */
	अगर (pm_suspend_शेष_s2idle() &&
	    serio == i8042_ports[I8042_KBD_PORT_NO].serio) अणु
		device_set_wakeup_enable(&serio->dev, true);
	पूर्ण

	spin_lock_irq(&i8042_lock);
	port->exists = true;
	spin_unlock_irq(&i8042_lock);

	वापस 0;
पूर्ण

/*
 * i8042_stop() marks serio port as non-existing so i8042_पूर्णांकerrupt
 * will not try to send data to the port that is about to go away.
 * The function is called by serio core as part of unरेजिस्टर procedure.
 */
अटल व्योम i8042_stop(काष्ठा serio *serio)
अणु
	काष्ठा i8042_port *port = serio->port_data;

	spin_lock_irq(&i8042_lock);
	port->exists = false;
	port->serio = शून्य;
	spin_unlock_irq(&i8042_lock);

	/*
	 * We need to make sure that पूर्णांकerrupt handler finishes using
	 * our serio port beक्रमe we वापस from this function.
	 * We synchronize with both AUX and KBD IRQs because there is
	 * a (very unlikely) chance that AUX IRQ is उठाओd क्रम KBD port
	 * and vice versa.
	 */
	synchronize_irq(I8042_AUX_IRQ);
	synchronize_irq(I8042_KBD_IRQ);
पूर्ण

/*
 * i8042_filter() filters out unwanted bytes from the input data stream.
 * It is called from i8042_पूर्णांकerrupt and thus is running with पूर्णांकerrupts
 * off and i8042_lock held.
 */
अटल bool i8042_filter(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
			 काष्ठा serio *serio)
अणु
	अगर (unlikely(i8042_suppress_kbd_ack)) अणु
		अगर ((~str & I8042_STR_AUXDATA) &&
		    (data == 0xfa || data == 0xfe)) अणु
			i8042_suppress_kbd_ack--;
			dbg("Extra keyboard ACK - filtered out\n");
			वापस true;
		पूर्ण
	पूर्ण

	अगर (i8042_platक्रमm_filter && i8042_platक्रमm_filter(data, str, serio)) अणु
		dbg("Filtered out by platform filter\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * i8042_पूर्णांकerrupt() is the most important function in this driver -
 * it handles the पूर्णांकerrupts from the i8042, and sends incoming bytes
 * to the upper layers.
 */

अटल irqवापस_t i8042_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i8042_port *port;
	काष्ठा serio *serio;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर str, data;
	अचिन्हित पूर्णांक dfl;
	अचिन्हित पूर्णांक port_no;
	bool filtered;
	पूर्णांक ret = 1;

	spin_lock_irqsave(&i8042_lock, flags);

	str = i8042_पढ़ो_status();
	अगर (unlikely(~str & I8042_STR_OBF)) अणु
		spin_unlock_irqrestore(&i8042_lock, flags);
		अगर (irq)
			dbg("Interrupt %d, without any data\n", irq);
		ret = 0;
		जाओ out;
	पूर्ण

	data = i8042_पढ़ो_data();

	अगर (i8042_mux_present && (str & I8042_STR_AUXDATA)) अणु
		अटल अचिन्हित दीर्घ last_transmit;
		अटल अचिन्हित अक्षर last_str;

		dfl = 0;
		अगर (str & I8042_STR_MUXERR) अणु
			dbg("MUX error, status is %02x, data is %02x\n",
			    str, data);
/*
 * When MUXERR condition is संकेतled the data रेजिस्टर can only contain
 * 0xfd, 0xfe or 0xff अगर implementation follows the spec. Unक्रमtunately
 * it is not always the हाल. Some KBCs also report 0xfc when there is
 * nothing connected to the port जबतक others someबार get confused which
 * port the data came from and संकेत error leaving the data पूर्णांकact. They
 * _करो not_ revert to legacy mode (actually I've never seen KBC reverting
 * to legacy mode yet, when we see one we'll add proper handling).
 * Anyway, we process 0xfc, 0xfd, 0xfe and 0xff as समयouts, and क्रम the
 * rest assume that the data came from the same serio last byte
 * was transmitted (अगर transmission happened not too दीर्घ ago).
 */

			चयन (data) अणु
				शेष:
					अगर (समय_beक्रमe(jअगरfies, last_transmit + HZ/10)) अणु
						str = last_str;
						अवरोध;
					पूर्ण
					fallthrough;	/* report समयout */
				हाल 0xfc:
				हाल 0xfd:
				हाल 0xfe: dfl = SERIO_TIMEOUT; data = 0xfe; अवरोध;
				हाल 0xff: dfl = SERIO_PARITY;  data = 0xfe; अवरोध;
			पूर्ण
		पूर्ण

		port_no = I8042_MUX_PORT_NO + ((str >> 6) & 3);
		last_str = str;
		last_transmit = jअगरfies;
	पूर्ण अन्यथा अणु

		dfl = ((str & I8042_STR_PARITY) ? SERIO_PARITY : 0) |
		      ((str & I8042_STR_TIMEOUT && !i8042_noसमयout) ? SERIO_TIMEOUT : 0);

		port_no = (str & I8042_STR_AUXDATA) ?
				I8042_AUX_PORT_NO : I8042_KBD_PORT_NO;
	पूर्ण

	port = &i8042_ports[port_no];
	serio = port->exists ? port->serio : शून्य;

	filter_dbg(port->driver_bound, data, "<- i8042 (interrupt, %d, %d%s%s)\n",
		   port_no, irq,
		   dfl & SERIO_PARITY ? ", bad parity" : "",
		   dfl & SERIO_TIMEOUT ? ", timeout" : "");

	filtered = i8042_filter(data, str, serio);

	spin_unlock_irqrestore(&i8042_lock, flags);

	अगर (likely(serio && !filtered))
		serio_पूर्णांकerrupt(serio, data, dfl);

 out:
	वापस IRQ_RETVAL(ret);
पूर्ण

/*
 * i8042_enable_kbd_port enables keyboard port on chip
 */

अटल पूर्णांक i8042_enable_kbd_port(व्योम)
अणु
	i8042_ctr &= ~I8042_CTR_KBDDIS;
	i8042_ctr |= I8042_CTR_KBDINT;

	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) अणु
		i8042_ctr &= ~I8042_CTR_KBDINT;
		i8042_ctr |= I8042_CTR_KBDDIS;
		pr_err("Failed to enable KBD port\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * i8042_enable_aux_port enables AUX (mouse) port on chip
 */

अटल पूर्णांक i8042_enable_aux_port(व्योम)
अणु
	i8042_ctr &= ~I8042_CTR_AUXDIS;
	i8042_ctr |= I8042_CTR_AUXINT;

	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) अणु
		i8042_ctr &= ~I8042_CTR_AUXINT;
		i8042_ctr |= I8042_CTR_AUXDIS;
		pr_err("Failed to enable AUX port\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * i8042_enable_mux_ports enables 4 inभागidual AUX ports after
 * the controller has been चयनed पूर्णांकo Multiplexed mode
 */

अटल पूर्णांक i8042_enable_mux_ports(व्योम)
अणु
	अचिन्हित अक्षर param;
	पूर्णांक i;

	क्रम (i = 0; i < I8042_NUM_MUX_PORTS; i++) अणु
		i8042_command(&param, I8042_CMD_MUX_PFX + i);
		i8042_command(&param, I8042_CMD_AUX_ENABLE);
	पूर्ण

	वापस i8042_enable_aux_port();
पूर्ण

/*
 * i8042_set_mux_mode checks whether the controller has an
 * active multiplexor and माला_दो the chip पूर्णांकo Multiplexed (true)
 * or Legacy (false) mode.
 */

अटल पूर्णांक i8042_set_mux_mode(bool multiplex, अचिन्हित अक्षर *mux_version)
अणु

	अचिन्हित अक्षर param, val;
/*
 * Get rid of bytes in the queue.
 */

	i8042_flush();

/*
 * Internal loopback test - send three bytes, they should come back from the
 * mouse पूर्णांकerface, the last should be version.
 */

	param = val = 0xf0;
	अगर (i8042_command(&param, I8042_CMD_AUX_LOOP) || param != val)
		वापस -1;
	param = val = multiplex ? 0x56 : 0xf6;
	अगर (i8042_command(&param, I8042_CMD_AUX_LOOP) || param != val)
		वापस -1;
	param = val = multiplex ? 0xa4 : 0xa5;
	अगर (i8042_command(&param, I8042_CMD_AUX_LOOP) || param == val)
		वापस -1;

/*
 * Workaround क्रम पूर्णांकerference with USB Legacy emulation
 * that causes a v10.12 MUX to be found.
 */
	अगर (param == 0xac)
		वापस -1;

	अगर (mux_version)
		*mux_version = param;

	वापस 0;
पूर्ण

/*
 * i8042_check_mux() checks whether the controller supports the PS/2 Active
 * Multiplexing specअगरication by Synaptics, Phoenix, Insyde and
 * LCS/Telegraphics.
 */

अटल पूर्णांक __init i8042_check_mux(व्योम)
अणु
	अचिन्हित अक्षर mux_version;

	अगर (i8042_set_mux_mode(true, &mux_version))
		वापस -1;

	pr_info("Detected active multiplexing controller, rev %d.%d\n",
		(mux_version >> 4) & 0xf, mux_version & 0xf);

/*
 * Disable all muxed ports by disabling AUX.
 */
	i8042_ctr |= I8042_CTR_AUXDIS;
	i8042_ctr &= ~I8042_CTR_AUXINT;

	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) अणु
		pr_err("Failed to disable AUX port, can't use MUX\n");
		वापस -EIO;
	पूर्ण

	i8042_mux_present = true;

	वापस 0;
पूर्ण

/*
 * The following is used to test AUX IRQ delivery.
 */
अटल काष्ठा completion i8042_aux_irq_delivered __initdata;
अटल bool i8042_irq_being_tested __initdata;

अटल irqवापस_t __init i8042_aux_test_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर str, data;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&i8042_lock, flags);
	str = i8042_पढ़ो_status();
	अगर (str & I8042_STR_OBF) अणु
		data = i8042_पढ़ो_data();
		dbg("%02x <- i8042 (aux_test_irq, %s)\n",
		    data, str & I8042_STR_AUXDATA ? "aux" : "kbd");
		अगर (i8042_irq_being_tested &&
		    data == 0xa5 && (str & I8042_STR_AUXDATA))
			complete(&i8042_aux_irq_delivered);
		ret = 1;
	पूर्ण
	spin_unlock_irqrestore(&i8042_lock, flags);

	वापस IRQ_RETVAL(ret);
पूर्ण

/*
 * i8042_toggle_aux - enables or disables AUX port on i8042 via command and
 * verअगरies success by पढ़ोinng CTR. Used when testing क्रम presence of AUX
 * port.
 */
अटल पूर्णांक __init i8042_toggle_aux(bool on)
अणु
	अचिन्हित अक्षर param;
	पूर्णांक i;

	अगर (i8042_command(&param,
			on ? I8042_CMD_AUX_ENABLE : I8042_CMD_AUX_DISABLE))
		वापस -1;

	/* some chips need some समय to set the I8042_CTR_AUXDIS bit */
	क्रम (i = 0; i < 100; i++) अणु
		udelay(50);

		अगर (i8042_command(&param, I8042_CMD_CTL_RCTR))
			वापस -1;

		अगर (!(param & I8042_CTR_AUXDIS) == on)
			वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * i8042_check_aux() applies as much paranoia as it can at detecting
 * the presence of an AUX पूर्णांकerface.
 */

अटल पूर्णांक __init i8042_check_aux(व्योम)
अणु
	पूर्णांक retval = -1;
	bool irq_रेजिस्टरed = false;
	bool aux_loop_broken = false;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर param;

/*
 * Get rid of bytes in the queue.
 */

	i8042_flush();

/*
 * Internal loopback test - filters out AT-type i8042's. Unक्रमtunately
 * SiS screwed up and their 5597 करोesn't support the LOOP command even
 * though it has an AUX port.
 */

	param = 0x5a;
	retval = i8042_command(&param, I8042_CMD_AUX_LOOP);
	अगर (retval || param != 0x5a) अणु

/*
 * External connection test - filters out AT-soldered PS/2 i8042's
 * 0x00 - no error, 0x01-0x03 - घड़ी/data stuck, 0xff - general error
 * 0xfa - no error on some notebooks which ignore the spec
 * Because it's common क्रम chipsets to वापस error on perfectly functioning
 * AUX ports, we test क्रम this only when the LOOP command failed.
 */

		अगर (i8042_command(&param, I8042_CMD_AUX_TEST) ||
		    (param && param != 0xfa && param != 0xff))
			वापस -1;

/*
 * If AUX_LOOP completed without error but वापसed unexpected data
 * mark it as broken
 */
		अगर (!retval)
			aux_loop_broken = true;
	पूर्ण

/*
 * Bit assignment test - filters out PS/2 i8042's in AT mode
 */

	अगर (i8042_toggle_aux(false)) अणु
		pr_warn("Failed to disable AUX port, but continuing anyway... Is this a SiS?\n");
		pr_warn("If AUX port is really absent please use the 'i8042.noaux' option\n");
	पूर्ण

	अगर (i8042_toggle_aux(true))
		वापस -1;

/*
 * Reset keyboard (needed on some laptops to successfully detect
 * touchpad, e.g., some Gigabyte laptop models with Elantech
 * touchpads).
 */
	अगर (i8042_kbdreset) अणु
		pr_warn("Attempting to reset device connected to KBD port\n");
		i8042_kbd_ग_लिखो(शून्य, (अचिन्हित अक्षर) 0xff);
	पूर्ण

/*
 * Test AUX IRQ delivery to make sure BIOS did not grab the IRQ and
 * used it क्रम a PCI card or somethig अन्यथा.
 */

	अगर (i8042_noloop || i8042_bypass_aux_irq_test || aux_loop_broken) अणु
/*
 * Without LOOP command we can't test AUX IRQ delivery. Assume the port
 * is working and hope we are right.
 */
		retval = 0;
		जाओ out;
	पूर्ण

	अगर (request_irq(I8042_AUX_IRQ, i8042_aux_test_irq, IRQF_SHARED,
			"i8042", i8042_platक्रमm_device))
		जाओ out;

	irq_रेजिस्टरed = true;

	अगर (i8042_enable_aux_port())
		जाओ out;

	spin_lock_irqsave(&i8042_lock, flags);

	init_completion(&i8042_aux_irq_delivered);
	i8042_irq_being_tested = true;

	param = 0xa5;
	retval = __i8042_command(&param, I8042_CMD_AUX_LOOP & 0xf0ff);

	spin_unlock_irqrestore(&i8042_lock, flags);

	अगर (retval)
		जाओ out;

	अगर (रुको_क्रम_completion_समयout(&i8042_aux_irq_delivered,
					msecs_to_jअगरfies(250)) == 0) अणु
/*
 * AUX IRQ was never delivered so we need to flush the controller to
 * get rid of the byte we put there; otherwise keyboard may not work.
 */
		dbg("     -- i8042 (aux irq test timeout)\n");
		i8042_flush();
		retval = -1;
	पूर्ण

 out:

/*
 * Disable the पूर्णांकerface.
 */

	i8042_ctr |= I8042_CTR_AUXDIS;
	i8042_ctr &= ~I8042_CTR_AUXINT;

	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR))
		retval = -1;

	अगर (irq_रेजिस्टरed)
		मुक्त_irq(I8042_AUX_IRQ, i8042_platक्रमm_device);

	वापस retval;
पूर्ण

अटल पूर्णांक i8042_controller_check(व्योम)
अणु
	अगर (i8042_flush()) अणु
		pr_info("No controller found\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i8042_controller_selftest(व्योम)
अणु
	अचिन्हित अक्षर param;
	पूर्णांक i = 0;

	/*
	 * We try this 5 बार; on some really fragile प्रणालीs this करोes not
	 * take the first समय...
	 */
	करो अणु

		अगर (i8042_command(&param, I8042_CMD_CTL_TEST)) अणु
			pr_err("i8042 controller selftest timeout\n");
			वापस -ENODEV;
		पूर्ण

		अगर (param == I8042_RET_CTL_TEST)
			वापस 0;

		dbg("i8042 controller selftest: %#x != %#x\n",
		    param, I8042_RET_CTL_TEST);
		msleep(50);
	पूर्ण जबतक (i++ < 5);

#अगर_घोषित CONFIG_X86
	/*
	 * On x86, we करोn't fail entire i8042 initialization अगर controller
	 * reset fails in hopes that keyboard port will still be functional
	 * and user will still get a working keyboard. This is especially
	 * important on netbooks. On other arches we trust hardware more.
	 */
	pr_info("giving up on controller selftest, continuing anyway...\n");
	वापस 0;
#अन्यथा
	pr_err("i8042 controller selftest failed\n");
	वापस -EIO;
#पूर्ण_अगर
पूर्ण

/*
 * i8042_controller init initializes the i8042 controller, and,
 * most importantly, sets it पूर्णांकo non-xlated mode अगर that's
 * desired.
 */

अटल पूर्णांक i8042_controller_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक n = 0;
	अचिन्हित अक्षर ctr[2];

/*
 * Save the CTR क्रम restore on unload / reboot.
 */

	करो अणु
		अगर (n >= 10) अणु
			pr_err("Unable to get stable CTR read\n");
			वापस -EIO;
		पूर्ण

		अगर (n != 0)
			udelay(50);

		अगर (i8042_command(&ctr[n++ % 2], I8042_CMD_CTL_RCTR)) अणु
			pr_err("Can't read CTR while initializing i8042\n");
			वापस -EIO;
		पूर्ण

	पूर्ण जबतक (n < 2 || ctr[0] != ctr[1]);

	i8042_initial_ctr = i8042_ctr = ctr[0];

/*
 * Disable the keyboard पूर्णांकerface and पूर्णांकerrupt.
 */

	i8042_ctr |= I8042_CTR_KBDDIS;
	i8042_ctr &= ~I8042_CTR_KBDINT;

/*
 * Handle keylock.
 */

	spin_lock_irqsave(&i8042_lock, flags);
	अगर (~i8042_पढ़ो_status() & I8042_STR_KEYLOCK) अणु
		अगर (i8042_unlock)
			i8042_ctr |= I8042_CTR_IGNKEYLOCK;
		अन्यथा
			pr_warn("Warning: Keylock active\n");
	पूर्ण
	spin_unlock_irqrestore(&i8042_lock, flags);

/*
 * If the chip is configured पूर्णांकo nontranslated mode by the BIOS, करोn't
 * bother enabling translating and be happy.
 */

	अगर (~i8042_ctr & I8042_CTR_XLATE)
		i8042_direct = true;

/*
 * Set nontranslated mode क्रम the kbd पूर्णांकerface अगर requested by an option.
 * After this the kbd पूर्णांकerface becomes a simple serial in/out, like the aux
 * पूर्णांकerface is. We करोn't करो this by शेष, since it can confuse notebook
 * BIOSes.
 */

	अगर (i8042_direct)
		i8042_ctr &= ~I8042_CTR_XLATE;

/*
 * Write CTR back.
 */

	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) अणु
		pr_err("Can't write CTR while initializing i8042\n");
		वापस -EIO;
	पूर्ण

/*
 * Flush whatever accumulated जबतक we were disabling keyboard port.
 */

	i8042_flush();

	वापस 0;
पूर्ण


/*
 * Reset the controller and reset CRT to the original value set by BIOS.
 */

अटल व्योम i8042_controller_reset(bool s2r_wants_reset)
अणु
	i8042_flush();

/*
 * Disable both KBD and AUX पूर्णांकerfaces so they करोn't get in the way
 */

	i8042_ctr |= I8042_CTR_KBDDIS | I8042_CTR_AUXDIS;
	i8042_ctr &= ~(I8042_CTR_KBDINT | I8042_CTR_AUXINT);

	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR))
		pr_warn("Can't write CTR while resetting\n");

/*
 * Disable MUX mode अगर present.
 */

	अगर (i8042_mux_present)
		i8042_set_mux_mode(false, शून्य);

/*
 * Reset the controller अगर requested.
 */

	अगर (i8042_reset == I8042_RESET_ALWAYS ||
	    (i8042_reset == I8042_RESET_ON_S2RAM && s2r_wants_reset)) अणु
		i8042_controller_selftest();
	पूर्ण

/*
 * Restore the original control रेजिस्टर setting.
 */

	अगर (i8042_command(&i8042_initial_ctr, I8042_CMD_CTL_WCTR))
		pr_warn("Can't restore CTR\n");
पूर्ण


/*
 * i8042_panic_blink() will turn the keyboard LEDs on or off and is called
 * when kernel panics. Flashing LEDs is useful क्रम users running X who may
 * not see the console and will help distinguishing panics from "real"
 * lockups.
 *
 * Note that DELAY has a limit of 10ms so we will not get stuck here
 * रुकोing क्रम KBC to मुक्त up even अगर KBD पूर्णांकerrupt is off
 */

#घोषणा DELAY करो अणु mdelay(1); अगर (++delay > 10) वापस delay; पूर्ण जबतक(0)

अटल दीर्घ i8042_panic_blink(पूर्णांक state)
अणु
	दीर्घ delay = 0;
	अक्षर led;

	led = (state) ? 0x01 | 0x04 : 0;
	जबतक (i8042_पढ़ो_status() & I8042_STR_IBF)
		DELAY;
	dbg("%02x -> i8042 (panic blink)\n", 0xed);
	i8042_suppress_kbd_ack = 2;
	i8042_ग_लिखो_data(0xed); /* set leds */
	DELAY;
	जबतक (i8042_पढ़ो_status() & I8042_STR_IBF)
		DELAY;
	DELAY;
	dbg("%02x -> i8042 (panic blink)\n", led);
	i8042_ग_लिखो_data(led);
	DELAY;
	वापस delay;
पूर्ण

#अघोषित DELAY

#अगर_घोषित CONFIG_X86
अटल व्योम i8042_dritek_enable(व्योम)
अणु
	अचिन्हित अक्षर param = 0x90;
	पूर्णांक error;

	error = i8042_command(&param, 0x1059);
	अगर (error)
		pr_warn("Failed to enable DRITEK extension: %d\n", error);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM

/*
 * Here we try to reset everything back to a state we had
 * beक्रमe suspending.
 */

अटल पूर्णांक i8042_controller_resume(bool s2r_wants_reset)
अणु
	पूर्णांक error;

	error = i8042_controller_check();
	अगर (error)
		वापस error;

	अगर (i8042_reset == I8042_RESET_ALWAYS ||
	    (i8042_reset == I8042_RESET_ON_S2RAM && s2r_wants_reset)) अणु
		error = i8042_controller_selftest();
		अगर (error)
			वापस error;
	पूर्ण

/*
 * Restore original CTR value and disable all ports
 */

	i8042_ctr = i8042_initial_ctr;
	अगर (i8042_direct)
		i8042_ctr &= ~I8042_CTR_XLATE;
	i8042_ctr |= I8042_CTR_AUXDIS | I8042_CTR_KBDDIS;
	i8042_ctr &= ~(I8042_CTR_AUXINT | I8042_CTR_KBDINT);
	अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) अणु
		pr_warn("Can't write CTR to resume, retrying...\n");
		msleep(50);
		अगर (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) अणु
			pr_err("CTR write retry failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण


#अगर_घोषित CONFIG_X86
	अगर (i8042_dritek)
		i8042_dritek_enable();
#पूर्ण_अगर

	अगर (i8042_mux_present) अणु
		अगर (i8042_set_mux_mode(true, शून्य) || i8042_enable_mux_ports())
			pr_warn("failed to resume active multiplexor, mouse won't work\n");
	पूर्ण अन्यथा अगर (i8042_ports[I8042_AUX_PORT_NO].serio)
		i8042_enable_aux_port();

	अगर (i8042_ports[I8042_KBD_PORT_NO].serio)
		i8042_enable_kbd_port();

	i8042_पूर्णांकerrupt(0, शून्य);

	वापस 0;
पूर्ण

/*
 * Here we try to restore the original BIOS settings to aव्योम
 * upsetting it.
 */

अटल पूर्णांक i8042_pm_suspend(काष्ठा device *dev)
अणु
	पूर्णांक i;

	अगर (pm_suspend_via_firmware())
		i8042_controller_reset(true);

	/* Set up serio पूर्णांकerrupts क्रम प्रणाली wakeup. */
	क्रम (i = 0; i < I8042_NUM_PORTS; i++) अणु
		काष्ठा serio *serio = i8042_ports[i].serio;

		अगर (serio && device_may_wakeup(&serio->dev))
			enable_irq_wake(i8042_ports[i].irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i8042_pm_resume_noirq(काष्ठा device *dev)
अणु
	अगर (!pm_resume_via_firmware())
		i8042_पूर्णांकerrupt(0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक i8042_pm_resume(काष्ठा device *dev)
अणु
	bool want_reset;
	पूर्णांक i;

	क्रम (i = 0; i < I8042_NUM_PORTS; i++) अणु
		काष्ठा serio *serio = i8042_ports[i].serio;

		अगर (serio && device_may_wakeup(&serio->dev))
			disable_irq_wake(i8042_ports[i].irq);
	पूर्ण

	/*
	 * If platक्रमm firmware was not going to be involved in suspend, we did
	 * not restore the controller state to whatever it had been at boot
	 * समय, so we करो not need to करो anything.
	 */
	अगर (!pm_suspend_via_firmware())
		वापस 0;

	/*
	 * We only need to reset the controller अगर we are resuming after handing
	 * off control to the platक्रमm firmware, otherwise we can simply restore
	 * the mode.
	 */
	want_reset = pm_resume_via_firmware();

	वापस i8042_controller_resume(want_reset);
पूर्ण

अटल पूर्णांक i8042_pm_thaw(काष्ठा device *dev)
अणु
	i8042_पूर्णांकerrupt(0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक i8042_pm_reset(काष्ठा device *dev)
अणु
	i8042_controller_reset(false);

	वापस 0;
पूर्ण

अटल पूर्णांक i8042_pm_restore(काष्ठा device *dev)
अणु
	वापस i8042_controller_resume(false);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops i8042_pm_ops = अणु
	.suspend	= i8042_pm_suspend,
	.resume_noirq	= i8042_pm_resume_noirq,
	.resume		= i8042_pm_resume,
	.thaw		= i8042_pm_thaw,
	.घातeroff	= i8042_pm_reset,
	.restore	= i8042_pm_restore,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PM */

/*
 * We need to reset the 8042 back to original mode on प्रणाली shutकरोwn,
 * because otherwise BIOSes will be confused.
 */

अटल व्योम i8042_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	i8042_controller_reset(false);
पूर्ण

अटल पूर्णांक __init i8042_create_kbd_port(व्योम)
अणु
	काष्ठा serio *serio;
	काष्ठा i8042_port *port = &i8042_ports[I8042_KBD_PORT_NO];

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!serio)
		वापस -ENOMEM;

	serio->id.type		= i8042_direct ? SERIO_8042 : SERIO_8042_XL;
	serio->ग_लिखो		= i8042_dumbkbd ? शून्य : i8042_kbd_ग_लिखो;
	serio->start		= i8042_start;
	serio->stop		= i8042_stop;
	serio->बंद		= i8042_port_बंद;
	serio->ps2_cmd_mutex	= &i8042_mutex;
	serio->port_data	= port;
	serio->dev.parent	= &i8042_platक्रमm_device->dev;
	strlcpy(serio->name, "i8042 KBD port", माप(serio->name));
	strlcpy(serio->phys, I8042_KBD_PHYS_DESC, माप(serio->phys));
	strlcpy(serio->firmware_id, i8042_kbd_firmware_id,
		माप(serio->firmware_id));
	set_primary_fwnode(&serio->dev, i8042_kbd_fwnode);

	port->serio = serio;
	port->irq = I8042_KBD_IRQ;

	वापस 0;
पूर्ण

अटल पूर्णांक __init i8042_create_aux_port(पूर्णांक idx)
अणु
	काष्ठा serio *serio;
	पूर्णांक port_no = idx < 0 ? I8042_AUX_PORT_NO : I8042_MUX_PORT_NO + idx;
	काष्ठा i8042_port *port = &i8042_ports[port_no];

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!serio)
		वापस -ENOMEM;

	serio->id.type		= SERIO_8042;
	serio->ग_लिखो		= i8042_aux_ग_लिखो;
	serio->start		= i8042_start;
	serio->stop		= i8042_stop;
	serio->ps2_cmd_mutex	= &i8042_mutex;
	serio->port_data	= port;
	serio->dev.parent	= &i8042_platक्रमm_device->dev;
	अगर (idx < 0) अणु
		strlcpy(serio->name, "i8042 AUX port", माप(serio->name));
		strlcpy(serio->phys, I8042_AUX_PHYS_DESC, माप(serio->phys));
		strlcpy(serio->firmware_id, i8042_aux_firmware_id,
			माप(serio->firmware_id));
		serio->बंद = i8042_port_बंद;
	पूर्ण अन्यथा अणु
		snम_लिखो(serio->name, माप(serio->name), "i8042 AUX%d port", idx);
		snम_लिखो(serio->phys, माप(serio->phys), I8042_MUX_PHYS_DESC, idx + 1);
		strlcpy(serio->firmware_id, i8042_aux_firmware_id,
			माप(serio->firmware_id));
	पूर्ण

	port->serio = serio;
	port->mux = idx;
	port->irq = I8042_AUX_IRQ;

	वापस 0;
पूर्ण

अटल व्योम __init i8042_मुक्त_kbd_port(व्योम)
अणु
	kमुक्त(i8042_ports[I8042_KBD_PORT_NO].serio);
	i8042_ports[I8042_KBD_PORT_NO].serio = शून्य;
पूर्ण

अटल व्योम __init i8042_मुक्त_aux_ports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = I8042_AUX_PORT_NO; i < I8042_NUM_PORTS; i++) अणु
		kमुक्त(i8042_ports[i].serio);
		i8042_ports[i].serio = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __init i8042_रेजिस्टर_ports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < I8042_NUM_PORTS; i++) अणु
		काष्ठा serio *serio = i8042_ports[i].serio;

		अगर (!serio)
			जारी;

		prपूर्णांकk(KERN_INFO "serio: %s at %#lx,%#lx irq %d\n",
			serio->name,
			(अचिन्हित दीर्घ) I8042_DATA_REG,
			(अचिन्हित दीर्घ) I8042_COMMAND_REG,
			i8042_ports[i].irq);
		serio_रेजिस्टर_port(serio);
	पूर्ण
पूर्ण

अटल व्योम i8042_unरेजिस्टर_ports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < I8042_NUM_PORTS; i++) अणु
		अगर (i8042_ports[i].serio) अणु
			serio_unरेजिस्टर_port(i8042_ports[i].serio);
			i8042_ports[i].serio = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम i8042_मुक्त_irqs(व्योम)
अणु
	अगर (i8042_aux_irq_रेजिस्टरed)
		मुक्त_irq(I8042_AUX_IRQ, i8042_platक्रमm_device);
	अगर (i8042_kbd_irq_रेजिस्टरed)
		मुक्त_irq(I8042_KBD_IRQ, i8042_platक्रमm_device);

	i8042_aux_irq_रेजिस्टरed = i8042_kbd_irq_रेजिस्टरed = false;
पूर्ण

अटल पूर्णांक __init i8042_setup_aux(व्योम)
अणु
	पूर्णांक (*aux_enable)(व्योम);
	पूर्णांक error;
	पूर्णांक i;

	अगर (i8042_check_aux())
		वापस -ENODEV;

	अगर (i8042_nomux || i8042_check_mux()) अणु
		error = i8042_create_aux_port(-1);
		अगर (error)
			जाओ err_मुक्त_ports;
		aux_enable = i8042_enable_aux_port;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < I8042_NUM_MUX_PORTS; i++) अणु
			error = i8042_create_aux_port(i);
			अगर (error)
				जाओ err_मुक्त_ports;
		पूर्ण
		aux_enable = i8042_enable_mux_ports;
	पूर्ण

	error = request_irq(I8042_AUX_IRQ, i8042_पूर्णांकerrupt, IRQF_SHARED,
			    "i8042", i8042_platक्रमm_device);
	अगर (error)
		जाओ err_मुक्त_ports;

	error = aux_enable();
	अगर (error)
		जाओ err_मुक्त_irq;

	i8042_aux_irq_रेजिस्टरed = true;
	वापस 0;

 err_मुक्त_irq:
	मुक्त_irq(I8042_AUX_IRQ, i8042_platक्रमm_device);
 err_मुक्त_ports:
	i8042_मुक्त_aux_ports();
	वापस error;
पूर्ण

अटल पूर्णांक __init i8042_setup_kbd(व्योम)
अणु
	पूर्णांक error;

	error = i8042_create_kbd_port();
	अगर (error)
		वापस error;

	error = request_irq(I8042_KBD_IRQ, i8042_पूर्णांकerrupt, IRQF_SHARED,
			    "i8042", i8042_platक्रमm_device);
	अगर (error)
		जाओ err_मुक्त_port;

	error = i8042_enable_kbd_port();
	अगर (error)
		जाओ err_मुक्त_irq;

	i8042_kbd_irq_रेजिस्टरed = true;
	वापस 0;

 err_मुक्त_irq:
	मुक्त_irq(I8042_KBD_IRQ, i8042_platक्रमm_device);
 err_मुक्त_port:
	i8042_मुक्त_kbd_port();
	वापस error;
पूर्ण

अटल पूर्णांक i8042_kbd_bind_notअगरier(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा i8042_port *port = serio->port_data;

	अगर (serio != i8042_ports[I8042_KBD_PORT_NO].serio)
		वापस 0;

	चयन (action) अणु
	हाल BUS_NOTIFY_BOUND_DRIVER:
		port->driver_bound = true;
		अवरोध;

	हाल BUS_NOTIFY_UNBIND_DRIVER:
		port->driver_bound = false;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init i8042_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक error;

	i8042_platक्रमm_device = dev;

	अगर (i8042_reset == I8042_RESET_ALWAYS) अणु
		error = i8042_controller_selftest();
		अगर (error)
			वापस error;
	पूर्ण

	error = i8042_controller_init();
	अगर (error)
		वापस error;

#अगर_घोषित CONFIG_X86
	अगर (i8042_dritek)
		i8042_dritek_enable();
#पूर्ण_अगर

	अगर (!i8042_noaux) अणु
		error = i8042_setup_aux();
		अगर (error && error != -ENODEV && error != -EBUSY)
			जाओ out_fail;
	पूर्ण

	अगर (!i8042_nokbd) अणु
		error = i8042_setup_kbd();
		अगर (error)
			जाओ out_fail;
	पूर्ण
/*
 * Ok, everything is पढ़ोy, let's रेजिस्टर all serio ports
 */
	i8042_रेजिस्टर_ports();

	वापस 0;

 out_fail:
	i8042_मुक्त_aux_ports();	/* in हाल KBD failed but AUX not */
	i8042_मुक्त_irqs();
	i8042_controller_reset(false);
	i8042_platक्रमm_device = शून्य;

	वापस error;
पूर्ण

अटल पूर्णांक i8042_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	i8042_unरेजिस्टर_ports();
	i8042_मुक्त_irqs();
	i8042_controller_reset(false);
	i8042_platक्रमm_device = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver i8042_driver = अणु
	.driver		= अणु
		.name	= "i8042",
#अगर_घोषित CONFIG_PM
		.pm	= &i8042_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.हटाओ		= i8042_हटाओ,
	.shutकरोwn	= i8042_shutकरोwn,
पूर्ण;

अटल काष्ठा notअगरier_block i8042_kbd_bind_notअगरier_block = अणु
	.notअगरier_call = i8042_kbd_bind_notअगरier,
पूर्ण;

अटल पूर्णांक __init i8042_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक err;

	dbg_init();

	err = i8042_platक्रमm_init();
	अगर (err)
		वापस (err == -ENODEV) ? 0 : err;

	err = i8042_controller_check();
	अगर (err)
		जाओ err_platक्रमm_निकास;

	/* Set this beक्रमe creating the dev to allow i8042_command to work right away */
	i8042_present = true;

	pdev = platक्रमm_create_bundle(&i8042_driver, i8042_probe, शून्य, 0, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		err = PTR_ERR(pdev);
		जाओ err_platक्रमm_निकास;
	पूर्ण

	bus_रेजिस्टर_notअगरier(&serio_bus, &i8042_kbd_bind_notअगरier_block);
	panic_blink = i8042_panic_blink;

	वापस 0;

 err_platक्रमm_निकास:
	i8042_platक्रमm_निकास();
	वापस err;
पूर्ण

अटल व्योम __निकास i8042_निकास(व्योम)
अणु
	अगर (!i8042_present)
		वापस;

	platक्रमm_device_unरेजिस्टर(i8042_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&i8042_driver);
	i8042_platक्रमm_निकास();

	bus_unरेजिस्टर_notअगरier(&serio_bus, &i8042_kbd_bind_notअगरier_block);
	panic_blink = शून्य;
पूर्ण

module_init(i8042_init);
module_निकास(i8042_निकास);
