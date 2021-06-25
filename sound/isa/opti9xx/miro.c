<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA soundcard driver क्रम Miro miroSOUND PCM1 pro
 *                                  miroSOUND PCM12
 *                                  miroSOUND PCM20 Radio
 *
 *   Copyright (C) 2004-2005 Martin Langer <martin-langer@gmx.de>
 *
 *   Based on OSS ACI and ALSA OPTi9xx drivers
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl4.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IOPORT
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>
#समावेश <sound/aci.h>

MODULE_AUTHOR("Martin Langer <martin-langer@gmx.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Miro miroSOUND PCM1 pro, PCM12, PCM20 Radio");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;		/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;		/* ID क्रम this card */
अटल दीर्घ port = SNDRV_DEFAULT_PORT1; 	/* 0x530,0xe80,0xf40,0x604 */
अटल दीर्घ mpu_port = SNDRV_DEFAULT_PORT1;	/* 0x300,0x310,0x320,0x330 */
अटल दीर्घ fm_port = SNDRV_DEFAULT_PORT1;	/* 0x388 */
अटल पूर्णांक irq = SNDRV_DEFAULT_IRQ1;		/* 5,7,9,10,11 */
अटल पूर्णांक mpu_irq = SNDRV_DEFAULT_IRQ1;	/* 5,7,9,10 */
अटल पूर्णांक dma1 = SNDRV_DEFAULT_DMA1;		/* 0,1,3 */
अटल पूर्णांक dma2 = SNDRV_DEFAULT_DMA1;		/* 0,1,3 */
अटल पूर्णांक wss;
अटल पूर्णांक ide;
#अगर_घोषित CONFIG_PNP
अटल bool isapnp = 1;				/* Enable ISA PnP detection */
#पूर्ण_अगर

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for miro soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for miro soundcard.");
module_param_hw(port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(port, "WSS port # for miro driver.");
module_param_hw(mpu_port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for miro driver.");
module_param_hw(fm_port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(fm_port, "FM Port # for miro driver.");
module_param_hw(irq, पूर्णांक, irq, 0444);
MODULE_PARM_DESC(irq, "WSS irq # for miro driver.");
module_param_hw(mpu_irq, पूर्णांक, irq, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 irq # for miro driver.");
module_param_hw(dma1, पूर्णांक, dma, 0444);
MODULE_PARM_DESC(dma1, "1st dma # for miro driver.");
module_param_hw(dma2, पूर्णांक, dma, 0444);
MODULE_PARM_DESC(dma2, "2nd dma # for miro driver.");
module_param(wss, पूर्णांक, 0444);
MODULE_PARM_DESC(wss, "wss mode");
module_param(ide, पूर्णांक, 0444);
MODULE_PARM_DESC(ide, "enable ide port");
#अगर_घोषित CONFIG_PNP
module_param(isapnp, bool, 0444);
MODULE_PARM_DESC(isapnp, "Enable ISA PnP detection for specified soundcard.");
#पूर्ण_अगर

#घोषणा OPTi9XX_HW_DETECT	0
#घोषणा OPTi9XX_HW_82C928	1
#घोषणा OPTi9XX_HW_82C929	2
#घोषणा OPTi9XX_HW_82C924	3
#घोषणा OPTi9XX_HW_82C925	4
#घोषणा OPTi9XX_HW_82C930	5
#घोषणा OPTi9XX_HW_82C931	6
#घोषणा OPTi9XX_HW_82C933	7
#घोषणा OPTi9XX_HW_LAST		OPTi9XX_HW_82C933

#घोषणा OPTi9XX_MC_REG(n)	n

काष्ठा snd_miro अणु
	अचिन्हित लघु hardware;
	अचिन्हित अक्षर password;
	अक्षर name[7];

	काष्ठा resource *res_mc_base;
	काष्ठा resource *res_aci_port;

	अचिन्हित दीर्घ mc_base;
	अचिन्हित दीर्घ mc_base_size;
	अचिन्हित दीर्घ pwd_reg;

	spinlock_t lock;
	काष्ठा snd_pcm *pcm;

	दीर्घ wss_base;
	पूर्णांक irq;
	पूर्णांक dma1;
	पूर्णांक dma2;

	दीर्घ mpu_port;
	पूर्णांक mpu_irq;

	काष्ठा snd_miro_aci *aci;
पूर्ण;

अटल काष्ठा snd_miro_aci aci_device;

अटल स्थिर अक्षर * स्थिर snd_opti9xx_names[] = अणु
	"unknown",
	"82C928", "82C929",
	"82C924", "82C925",
	"82C930", "82C931", "82C933"
पूर्ण;

अटल पूर्णांक snd_miro_pnp_is_probed;

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_card_device_id snd_miro_pnpids[] = अणु
	/* PCM20 and PCM12 in PnP mode */
	अणु .id = "MIR0924",
	  .devs = अणु अणु "MIR0000" पूर्ण, अणु "MIR0002" पूर्ण, अणु "MIR0005" पूर्ण पूर्ण, पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_miro_pnpids);

#पूर्ण_अगर	/* CONFIG_PNP */

/* 
 *  ACI control
 */

अटल पूर्णांक aci_busy_रुको(काष्ठा snd_miro_aci *aci)
अणु
	दीर्घ समयout;
	अचिन्हित अक्षर byte;

	क्रम (समयout = 1; समयout <= ACI_MINTIME + 30; समयout++) अणु
		byte = inb(aci->aci_port + ACI_REG_BUSY);
		अगर ((byte & 1) == 0) अणु
			अगर (समयout >= ACI_MINTIME)
				snd_prपूर्णांकd("aci ready in round %ld.\n",
					   समयout-ACI_MINTIME);
			वापस byte;
		पूर्ण
		अगर (समयout >= ACI_MINTIME) अणु
			दीर्घ out=10*HZ;
			चयन (समयout-ACI_MINTIME) अणु
			हाल 0 ... 9:
				out /= 10;
				fallthrough;
			हाल 10 ... 19:
				out /= 10;
				fallthrough;
			हाल 20 ... 30:
				out /= 10;
				fallthrough;
			शेष:
				set_current_state(TASK_UNINTERRUPTIBLE);
				schedule_समयout(out);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	snd_prपूर्णांकk(KERN_ERR "aci_busy_wait() time out\n");
	वापस -EBUSY;
पूर्ण

अटल अंतरभूत पूर्णांक aci_ग_लिखो(काष्ठा snd_miro_aci *aci, अचिन्हित अक्षर byte)
अणु
	अगर (aci_busy_रुको(aci) >= 0) अणु
		outb(byte, aci->aci_port + ACI_REG_COMMAND);
		वापस 0;
	पूर्ण अन्यथा अणु
		snd_prपूर्णांकk(KERN_ERR "aci busy, aci_write(0x%x) stopped.\n", byte);
		वापस -EBUSY;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक aci_पढ़ो(काष्ठा snd_miro_aci *aci)
अणु
	अचिन्हित अक्षर byte;

	अगर (aci_busy_रुको(aci) >= 0) अणु
		byte = inb(aci->aci_port + ACI_REG_STATUS);
		वापस byte;
	पूर्ण अन्यथा अणु
		snd_prपूर्णांकk(KERN_ERR "aci busy, aci_read() stopped.\n");
		वापस -EBUSY;
	पूर्ण
पूर्ण

पूर्णांक snd_aci_cmd(काष्ठा snd_miro_aci *aci, पूर्णांक ग_लिखो1, पूर्णांक ग_लिखो2, पूर्णांक ग_लिखो3)
अणु
	पूर्णांक ग_लिखो[] = अणुग_लिखो1, ग_लिखो2, ग_लिखो3पूर्ण;
	पूर्णांक value, i;

	अगर (mutex_lock_पूर्णांकerruptible(&aci->aci_mutex))
		वापस -EINTR;

	क्रम (i=0; i<3; i++) अणु
		अगर (ग_लिखो[i]< 0 || ग_लिखो[i] > 255)
			अवरोध;
		अन्यथा अणु
			value = aci_ग_लिखो(aci, ग_लिखो[i]);
			अगर (value < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	value = aci_पढ़ो(aci);

out:	mutex_unlock(&aci->aci_mutex);
	वापस value;
पूर्ण
EXPORT_SYMBOL(snd_aci_cmd);

अटल पूर्णांक aci_getvalue(काष्ठा snd_miro_aci *aci, अचिन्हित अक्षर index)
अणु
	वापस snd_aci_cmd(aci, ACI_STATUS, index, -1);
पूर्ण

अटल पूर्णांक aci_setvalue(काष्ठा snd_miro_aci *aci, अचिन्हित अक्षर index,
			पूर्णांक value)
अणु
	वापस snd_aci_cmd(aci, index, value, -1);
पूर्ण

काष्ठा snd_miro_aci *snd_aci_get_aci(व्योम)
अणु
	अगर (aci_device.aci_port == 0)
		वापस शून्य;
	वापस &aci_device;
पूर्ण
EXPORT_SYMBOL(snd_aci_get_aci);

/*
 *  MIXER part
 */

#घोषणा snd_miro_info_capture	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_miro_get_capture(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	पूर्णांक value;

	value = aci_getvalue(miro->aci, ACI_S_GENERAL);
	अगर (value < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "snd_miro_get_capture() failed: %d\n",
			   value);
		वापस value;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[0] = value & 0x20;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_put_capture(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, value, error;

	value = !(ucontrol->value.पूर्णांकeger.value[0]);

	error = aci_setvalue(miro->aci, ACI_SET_SOLOMODE, value);
	अगर (error < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "snd_miro_put_capture() failed: %d\n",
			   error);
		वापस error;
	पूर्ण

	change = (value != miro->aci->aci_solomode);
	miro->aci->aci_solomode = value;
	
	वापस change;
पूर्ण

अटल पूर्णांक snd_miro_info_preamp(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 3;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_get_preamp(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	पूर्णांक value;

	अगर (miro->aci->aci_version <= 176) अणु

		/* 
		   OSS says it's not पढ़ोable with versions < 176.
		   But it करोesn't work on my card,
		   which is a PCM12 with aci_version = 176.
		*/

		ucontrol->value.पूर्णांकeger.value[0] = miro->aci->aci_preamp;
		वापस 0;
	पूर्ण

	value = aci_getvalue(miro->aci, ACI_GET_PREAMP);
	अगर (value < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "snd_miro_get_preamp() failed: %d\n",
			   value);
		वापस value;
	पूर्ण
	
	ucontrol->value.पूर्णांकeger.value[0] = value;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_put_preamp(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	पूर्णांक error, value, change;

	value = ucontrol->value.पूर्णांकeger.value[0];

	error = aci_setvalue(miro->aci, ACI_SET_PREAMP, value);
	अगर (error < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "snd_miro_put_preamp() failed: %d\n",
			   error);
		वापस error;
	पूर्ण

	change = (value != miro->aci->aci_preamp);
	miro->aci->aci_preamp = value;

	वापस change;
पूर्ण

#घोषणा snd_miro_info_amp	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_miro_get_amp(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = miro->aci->aci_amp;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_put_amp(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	पूर्णांक error, value, change;

	value = ucontrol->value.पूर्णांकeger.value[0];

	error = aci_setvalue(miro->aci, ACI_SET_POWERAMP, value);
	अगर (error < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "snd_miro_put_amp() to %d failed: %d\n", value, error);
		वापस error;
	पूर्ण

	change = (value != miro->aci->aci_amp);
	miro->aci->aci_amp = value;

	वापस change;
पूर्ण

#घोषणा MIRO_DOUBLE(ctl_name, ctl_index, get_right_reg, set_right_reg) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = ctl_name, \
  .index = ctl_index, \
  .info = snd_miro_info_द्विगुन, \
  .get = snd_miro_get_द्विगुन, \
  .put = snd_miro_put_द्विगुन, \
  .निजी_value = get_right_reg | (set_right_reg << 8) \
पूर्ण

अटल पूर्णांक snd_miro_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, 
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक reg = kcontrol->निजी_value & 0xff;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;

	अगर ((reg >= ACI_GET_EQ1) && (reg <= ACI_GET_EQ7)) अणु

		/* equalizer elements */

		uinfo->value.पूर्णांकeger.min = - 0x7f;
		uinfo->value.पूर्णांकeger.max = 0x7f;
	पूर्ण अन्यथा अणु

		/* non-equalizer elements */

		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = 0x20;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, 
			       काष्ठा snd_ctl_elem_value *uinfo)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_val, right_val;

	पूर्णांक right_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक left_reg = right_reg + 1;

	right_val = aci_getvalue(miro->aci, right_reg);
	अगर (right_val < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "aci_getvalue(%d) failed: %d\n", right_reg, right_val);
		वापस right_val;
	पूर्ण

	left_val = aci_getvalue(miro->aci, left_reg);
	अगर (left_val < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "aci_getvalue(%d) failed: %d\n", left_reg, left_val);
		वापस left_val;
	पूर्ण

	अगर ((right_reg >= ACI_GET_EQ1) && (right_reg <= ACI_GET_EQ7)) अणु

		/* equalizer elements */

		अगर (left_val < 0x80) अणु
			uinfo->value.पूर्णांकeger.value[0] = left_val;
		पूर्ण अन्यथा अणु
			uinfo->value.पूर्णांकeger.value[0] = 0x80 - left_val;
		पूर्ण

		अगर (right_val < 0x80) अणु
			uinfo->value.पूर्णांकeger.value[1] = right_val;
		पूर्ण अन्यथा अणु
			uinfo->value.पूर्णांकeger.value[1] = 0x80 - right_val;
		पूर्ण

	पूर्ण अन्यथा अणु

		/* non-equalizer elements */

		uinfo->value.पूर्णांकeger.value[0] = 0x20 - left_val;
		uinfo->value.पूर्णांकeger.value[1] = 0x20 - right_val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, 
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_miro *miro = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_miro_aci *aci = miro->aci;
	पूर्णांक left, right, left_old, right_old;
	पूर्णांक setreg_left, setreg_right, getreg_left, getreg_right;
	पूर्णांक change, error;

	left = ucontrol->value.पूर्णांकeger.value[0];
	right = ucontrol->value.पूर्णांकeger.value[1];

	setreg_right = (kcontrol->निजी_value >> 8) & 0xff;
	setreg_left = setreg_right + 8;
	अगर (setreg_right == ACI_SET_MASTER)
		setreg_left -= 7;

	getreg_right = kcontrol->निजी_value & 0xff;
	getreg_left = getreg_right + 1;

	left_old = aci_getvalue(aci, getreg_left);
	अगर (left_old < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "aci_getvalue(%d) failed: %d\n", getreg_left, left_old);
		वापस left_old;
	पूर्ण

	right_old = aci_getvalue(aci, getreg_right);
	अगर (right_old < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "aci_getvalue(%d) failed: %d\n", getreg_right, right_old);
		वापस right_old;
	पूर्ण

	अगर ((getreg_right >= ACI_GET_EQ1) && (getreg_right <= ACI_GET_EQ7)) अणु

		/* equalizer elements */

		अगर (left < -0x7f || left > 0x7f ||
		    right < -0x7f || right > 0x7f)
			वापस -EINVAL;

		अगर (left_old > 0x80) 
			left_old = 0x80 - left_old;
		अगर (right_old > 0x80) 
			right_old = 0x80 - right_old;

		अगर (left >= 0) अणु
			error = aci_setvalue(aci, setreg_left, left);
			अगर (error < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "aci_setvalue(%d) failed: %d\n",
					   left, error);
				वापस error;
			पूर्ण
		पूर्ण अन्यथा अणु
			error = aci_setvalue(aci, setreg_left, 0x80 - left);
			अगर (error < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "aci_setvalue(%d) failed: %d\n",
					   0x80 - left, error);
				वापस error;
			पूर्ण
		पूर्ण

		अगर (right >= 0) अणु
			error = aci_setvalue(aci, setreg_right, right);
			अगर (error < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "aci_setvalue(%d) failed: %d\n",
					   right, error);
				वापस error;
			पूर्ण
		पूर्ण अन्यथा अणु
			error = aci_setvalue(aci, setreg_right, 0x80 - right);
			अगर (error < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "aci_setvalue(%d) failed: %d\n",
					   0x80 - right, error);
				वापस error;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु

		/* non-equalizer elements */

		अगर (left < 0 || left > 0x20 ||
		    right < 0 || right > 0x20)
			वापस -EINVAL;

		left_old = 0x20 - left_old;
		right_old = 0x20 - right_old;

		error = aci_setvalue(aci, setreg_left, 0x20 - left);
		अगर (error < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "aci_setvalue(%d) failed: %d\n",
				   0x20 - left, error);
			वापस error;
		पूर्ण
		error = aci_setvalue(aci, setreg_right, 0x20 - right);
		अगर (error < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "aci_setvalue(%d) failed: %d\n",
				   0x20 - right, error);
			वापस error;
		पूर्ण
	पूर्ण

	change = (left != left_old) || (right != right_old);

	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_miro_controls[] = अणु
MIRO_DOUBLE("Master Playback Volume", 0, ACI_GET_MASTER, ACI_SET_MASTER),
MIRO_DOUBLE("Mic Playback Volume", 1, ACI_GET_MIC, ACI_SET_MIC),
MIRO_DOUBLE("Line Playback Volume", 1, ACI_GET_LINE, ACI_SET_LINE),
MIRO_DOUBLE("CD Playback Volume", 0, ACI_GET_CD, ACI_SET_CD),
MIRO_DOUBLE("Synth Playback Volume", 0, ACI_GET_SYNTH, ACI_SET_SYNTH),
MIRO_DOUBLE("PCM Playback Volume", 1, ACI_GET_PCM, ACI_SET_PCM),
MIRO_DOUBLE("Aux Playback Volume", 2, ACI_GET_LINE2, ACI_SET_LINE2),
पूर्ण;

/* Equalizer with seven bands (only PCM20) 
   from -12dB up to +12dB on each band */
अटल स्थिर काष्ठा snd_kcontrol_new snd_miro_eq_controls[] = अणु
MIRO_DOUBLE("Tone Control - 28 Hz", 0, ACI_GET_EQ1, ACI_SET_EQ1),
MIRO_DOUBLE("Tone Control - 160 Hz", 0, ACI_GET_EQ2, ACI_SET_EQ2),
MIRO_DOUBLE("Tone Control - 400 Hz", 0, ACI_GET_EQ3, ACI_SET_EQ3),
MIRO_DOUBLE("Tone Control - 1 kHz", 0, ACI_GET_EQ4, ACI_SET_EQ4),
MIRO_DOUBLE("Tone Control - 2.5 kHz", 0, ACI_GET_EQ5, ACI_SET_EQ5),
MIRO_DOUBLE("Tone Control - 6.3 kHz", 0, ACI_GET_EQ6, ACI_SET_EQ6),
MIRO_DOUBLE("Tone Control - 16 kHz", 0, ACI_GET_EQ7, ACI_SET_EQ7),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_miro_radio_control[] = अणु
MIRO_DOUBLE("Radio Playback Volume", 0, ACI_GET_LINE1, ACI_SET_LINE1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_miro_line_control[] = अणु
MIRO_DOUBLE("Line Playback Volume", 2, ACI_GET_LINE1, ACI_SET_LINE1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_miro_preamp_control[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Mic Boost",
	.index = 1,
	.info = snd_miro_info_preamp,
	.get = snd_miro_get_preamp,
	.put = snd_miro_put_preamp,
पूर्णपूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_miro_amp_control[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Line Boost",
	.index = 0,
	.info = snd_miro_info_amp,
	.get = snd_miro_get_amp,
	.put = snd_miro_put_amp,
पूर्णपूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_miro_capture_control[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Capture Switch",
	.index = 0,
	.info = snd_miro_info_capture,
	.get = snd_miro_get_capture,
	.put = snd_miro_put_capture,
पूर्णपूर्ण;

अटल स्थिर अचिन्हित अक्षर aci_init_values[][2] = अणु
	अणु ACI_SET_MUTE, 0x00 पूर्ण,
	अणु ACI_SET_POWERAMP, 0x00 पूर्ण,
	अणु ACI_SET_PREAMP, 0x00 पूर्ण,
	अणु ACI_SET_SOLOMODE, 0x00 पूर्ण,
	अणु ACI_SET_MIC + 0, 0x20 पूर्ण,
	अणु ACI_SET_MIC + 8, 0x20 पूर्ण,
	अणु ACI_SET_LINE + 0, 0x20 पूर्ण,
	अणु ACI_SET_LINE + 8, 0x20 पूर्ण,
	अणु ACI_SET_CD + 0, 0x20 पूर्ण,
	अणु ACI_SET_CD + 8, 0x20 पूर्ण,
	अणु ACI_SET_PCM + 0, 0x20 पूर्ण,
	अणु ACI_SET_PCM + 8, 0x20 पूर्ण,
	अणु ACI_SET_LINE1 + 0, 0x20 पूर्ण,
	अणु ACI_SET_LINE1 + 8, 0x20 पूर्ण,
	अणु ACI_SET_LINE2 + 0, 0x20 पूर्ण,
	अणु ACI_SET_LINE2 + 8, 0x20 पूर्ण,
	अणु ACI_SET_SYNTH + 0, 0x20 पूर्ण,
	अणु ACI_SET_SYNTH + 8, 0x20 पूर्ण,
	अणु ACI_SET_MASTER + 0, 0x20 पूर्ण,
	अणु ACI_SET_MASTER + 1, 0x20 पूर्ण,
पूर्ण;

अटल पूर्णांक snd_set_aci_init_values(काष्ठा snd_miro *miro)
अणु
	पूर्णांक idx, error;
	काष्ठा snd_miro_aci *aci = miro->aci;

	/* enable WSS on PCM1 */

	अगर ((aci->aci_product == 'A') && wss) अणु
		error = aci_setvalue(aci, ACI_SET_WSS, wss);
		अगर (error < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "enabling WSS mode failed\n");
			वापस error;
		पूर्ण
	पूर्ण

	/* enable IDE port */

	अगर (ide) अणु
		error = aci_setvalue(aci, ACI_SET_IDE, ide);
		अगर (error < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "enabling IDE port failed\n");
			वापस error;
		पूर्ण
	पूर्ण

	/* set common aci values */

	क्रम (idx = 0; idx < ARRAY_SIZE(aci_init_values); idx++) अणु
		error = aci_setvalue(aci, aci_init_values[idx][0],
				     aci_init_values[idx][1]);
		अगर (error < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "aci_setvalue(%d) failed: %d\n", 
				   aci_init_values[idx][0], error);
                        वापस error;
                पूर्ण
	पूर्ण
	aci->aci_amp = 0;
	aci->aci_preamp = 0;
	aci->aci_solomode = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_mixer(काष्ठा snd_card *card,
			  काष्ठा snd_miro *miro)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!miro || !card))
		वापस -EINVAL;

	चयन (miro->hardware) अणु
	हाल OPTi9XX_HW_82C924:
		म_नकल(card->mixername, "ACI & OPTi924");
		अवरोध;
	हाल OPTi9XX_HW_82C929:
		म_नकल(card->mixername, "ACI & OPTi929");
		अवरोध;
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_miro_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_controls[idx], miro))) < 0)
			वापस err;
	पूर्ण

	अगर ((miro->aci->aci_product == 'A') ||
	    (miro->aci->aci_product == 'B')) अणु
		/* PCM1/PCM12 with घातer-amp and Line 2 */
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_line_control[0], miro))) < 0)
			वापस err;
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_amp_control[0], miro))) < 0)
			वापस err;
	पूर्ण

	अगर ((miro->aci->aci_product == 'B') ||
	    (miro->aci->aci_product == 'C')) अणु
		/* PCM12/PCM20 with mic-preamp */
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_preamp_control[0], miro))) < 0)
			वापस err;
		अगर (miro->aci->aci_version >= 176)
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_capture_control[0], miro))) < 0)
				वापस err;
	पूर्ण

	अगर (miro->aci->aci_product == 'C') अणु
		/* PCM20 with radio and 7 band equalizer */
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_radio_control[0], miro))) < 0)
			वापस err;
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_miro_eq_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_miro_eq_controls[idx], miro))) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_init(काष्ठा snd_miro *chip,
			 अचिन्हित लघु hardware)
अणु
	अटल स्थिर पूर्णांक opti9xx_mc_size[] = अणु7, 7, 10, 10, 2, 2, 2पूर्ण;

	chip->hardware = hardware;
	म_नकल(chip->name, snd_opti9xx_names[hardware]);

	chip->mc_base_size = opti9xx_mc_size[hardware];  

	spin_lock_init(&chip->lock);

	chip->wss_base = -1;
	chip->irq = -1;
	chip->dma1 = -1;
	chip->dma2 = -1;
	chip->mpu_port = -1;
	chip->mpu_irq = -1;

	chip->pwd_reg = 3;

#अगर_घोषित CONFIG_PNP
	अगर (isapnp && chip->mc_base)
		/* PnP resource gives the least 10 bits */
		chip->mc_base |= 0xc00;
	अन्यथा
#पूर्ण_अगर
		chip->mc_base = 0xf8c;

	चयन (hardware) अणु
	हाल OPTi9XX_HW_82C929:
		chip->password = 0xe3;
		अवरोध;

	हाल OPTi9XX_HW_82C924:
		chip->password = 0xe5;
		अवरोध;

	शेष:
		snd_prपूर्णांकk(KERN_ERR "sorry, no support for %d\n", hardware);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर snd_miro_पढ़ो(काष्ठा snd_miro *chip,
				   अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर retval = 0xff;

	spin_lock_irqsave(&chip->lock, flags);
	outb(chip->password, chip->mc_base + chip->pwd_reg);

	चयन (chip->hardware) अणु
	हाल OPTi9XX_HW_82C924:
		अगर (reg > 7) अणु
			outb(reg, chip->mc_base + 8);
			outb(chip->password, chip->mc_base + chip->pwd_reg);
			retval = inb(chip->mc_base + 9);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल OPTi9XX_HW_82C929:
		retval = inb(chip->mc_base + reg);
		अवरोध;

	शेष:
		snd_prपूर्णांकk(KERN_ERR "sorry, no support for %d\n", chip->hardware);
	पूर्ण

	spin_unlock_irqrestore(&chip->lock, flags);
	वापस retval;
पूर्ण

अटल व्योम snd_miro_ग_लिखो(काष्ठा snd_miro *chip, अचिन्हित अक्षर reg,
			   अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	outb(chip->password, chip->mc_base + chip->pwd_reg);

	चयन (chip->hardware) अणु
	हाल OPTi9XX_HW_82C924:
		अगर (reg > 7) अणु
			outb(reg, chip->mc_base + 8);
			outb(chip->password, chip->mc_base + chip->pwd_reg);
			outb(value, chip->mc_base + 9);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल OPTi9XX_HW_82C929:
		outb(value, chip->mc_base + reg);
		अवरोध;

	शेष:
		snd_prपूर्णांकk(KERN_ERR "sorry, no support for %d\n", chip->hardware);
	पूर्ण

	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल अंतरभूत व्योम snd_miro_ग_लिखो_mask(काष्ठा snd_miro *chip,
		अचिन्हित अक्षर reg, अचिन्हित अक्षर value, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर oldval = snd_miro_पढ़ो(chip, reg);

	snd_miro_ग_लिखो(chip, reg, (oldval & ~mask) | (value & mask));
पूर्ण

/*
 *  Proc Interface
 */

अटल व्योम snd_miro_proc_पढ़ो(काष्ठा snd_info_entry * entry, 
			       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_miro *miro = (काष्ठा snd_miro *) entry->निजी_data;
	काष्ठा snd_miro_aci *aci = miro->aci;
	अक्षर* model = "unknown";

	/* miroSOUND PCM1 pro, early PCM12 */

	अगर ((miro->hardware == OPTi9XX_HW_82C929) &&
	    (aci->aci_venकरोr == 'm') &&
	    (aci->aci_product == 'A')) अणु
		चयन (aci->aci_version) अणु
		हाल 3:
			model = "miroSOUND PCM1 pro";
			अवरोध;
		शेष:
			model = "miroSOUND PCM1 pro / (early) PCM12";
			अवरोध;
		पूर्ण
	पूर्ण

	/* miroSOUND PCM12, PCM12 (Rev. E), PCM12 pnp */

	अगर ((miro->hardware == OPTi9XX_HW_82C924) &&
	    (aci->aci_venकरोr == 'm') &&
	    (aci->aci_product == 'B')) अणु
		चयन (aci->aci_version) अणु
		हाल 4:
			model = "miroSOUND PCM12";
			अवरोध;
		हाल 176:
			model = "miroSOUND PCM12 (Rev. E)";
			अवरोध;
		शेष:
			model = "miroSOUND PCM12 / PCM12 pnp";
			अवरोध;
		पूर्ण
	पूर्ण

	/* miroSOUND PCM20 radio */

	अगर ((miro->hardware == OPTi9XX_HW_82C924) &&
	    (aci->aci_venकरोr == 'm') &&
	    (aci->aci_product == 'C')) अणु
		चयन (aci->aci_version) अणु
		हाल 7:
			model = "miroSOUND PCM20 radio (Rev. E)";
			अवरोध;
		शेष:
			model = "miroSOUND PCM20 radio";
			अवरोध;
		पूर्ण
	पूर्ण

	snd_iम_लिखो(buffer, "\nGeneral information:\n");
	snd_iम_लिखो(buffer, "  model   : %s\n", model);
	snd_iम_लिखो(buffer, "  opti    : %s\n", miro->name);
	snd_iम_लिखो(buffer, "  codec   : %s\n", miro->pcm->name);
	snd_iम_लिखो(buffer, "  port    : 0x%lx\n", miro->wss_base);
	snd_iम_लिखो(buffer, "  irq     : %d\n", miro->irq);
	snd_iम_लिखो(buffer, "  dma     : %d,%d\n\n", miro->dma1, miro->dma2);

	snd_iम_लिखो(buffer, "MPU-401:\n");
	snd_iम_लिखो(buffer, "  port    : 0x%lx\n", miro->mpu_port);
	snd_iम_लिखो(buffer, "  irq     : %d\n\n", miro->mpu_irq);

	snd_iम_लिखो(buffer, "ACI information:\n");
	snd_iम_लिखो(buffer, "  vendor  : ");
	चयन (aci->aci_venकरोr) अणु
	हाल 'm':
		snd_iम_लिखो(buffer, "Miro\n");
		अवरोध;
	शेष:
		snd_iम_लिखो(buffer, "unknown (0x%x)\n", aci->aci_venकरोr);
		अवरोध;
	पूर्ण

	snd_iम_लिखो(buffer, "  product : ");
	चयन (aci->aci_product) अणु
	हाल 'A':
		snd_iम_लिखो(buffer, "miroSOUND PCM1 pro / (early) PCM12\n");
		अवरोध;
	हाल 'B':
		snd_iम_लिखो(buffer, "miroSOUND PCM12\n");
		अवरोध;
	हाल 'C':
		snd_iम_लिखो(buffer, "miroSOUND PCM20 radio\n");
		अवरोध;
	शेष:
		snd_iम_लिखो(buffer, "unknown (0x%x)\n", aci->aci_product);
		अवरोध;
	पूर्ण

	snd_iम_लिखो(buffer, "  firmware: %d (0x%x)\n",
		    aci->aci_version, aci->aci_version);
	snd_iम_लिखो(buffer, "  port    : 0x%lx-0x%lx\n", 
		    aci->aci_port, aci->aci_port+2);
	snd_iम_लिखो(buffer, "  wss     : 0x%x\n", wss);
	snd_iम_लिखो(buffer, "  ide     : 0x%x\n", ide);
	snd_iम_लिखो(buffer, "  solomode: 0x%x\n", aci->aci_solomode);
	snd_iम_लिखो(buffer, "  amp     : 0x%x\n", aci->aci_amp);
	snd_iम_लिखो(buffer, "  preamp  : 0x%x\n", aci->aci_preamp);
पूर्ण

अटल व्योम snd_miro_proc_init(काष्ठा snd_card *card,
			       काष्ठा snd_miro *miro)
अणु
	snd_card_ro_proc_new(card, "miro", miro, snd_miro_proc_पढ़ो);
पूर्ण

/*
 *  Init
 */

अटल पूर्णांक snd_miro_configure(काष्ठा snd_miro *chip)
अणु
	अचिन्हित अक्षर wss_base_bits;
	अचिन्हित अक्षर irq_bits;
	अचिन्हित अक्षर dma_bits;
	अचिन्हित अक्षर mpu_port_bits = 0;
	अचिन्हित अक्षर mpu_irq_bits;
	अचिन्हित दीर्घ flags;

	snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(1), 0x80, 0x80);
	snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(2), 0x20, 0x20); /* OPL4 */
	snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(5), 0x02, 0x02);

	चयन (chip->hardware) अणु
	हाल OPTi9XX_HW_82C924:
		snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(6), 0x02, 0x02);
		snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(3), 0xf0, 0xff);
		अवरोध;
	हाल OPTi9XX_HW_82C929:
		/* untested init commands क्रम OPTi929 */
		snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(4), 0x00, 0x0c);
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "chip %d not supported\n", chip->hardware);
		वापस -EINVAL;
	पूर्ण

	/* PnP resource says it decodes only 10 bits of address */
	चयन (chip->wss_base & 0x3ff) अणु
	हाल 0x130:
		chip->wss_base = 0x530;
		wss_base_bits = 0x00;
		अवरोध;
	हाल 0x204:
		chip->wss_base = 0x604;
		wss_base_bits = 0x03;
		अवरोध;
	हाल 0x280:
		chip->wss_base = 0xe80;
		wss_base_bits = 0x01;
		अवरोध;
	हाल 0x340:
		chip->wss_base = 0xf40;
		wss_base_bits = 0x02;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "WSS port 0x%lx not valid\n", chip->wss_base);
		जाओ __skip_base;
	पूर्ण
	snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(1), wss_base_bits << 4, 0x30);

__skip_base:
	चयन (chip->irq) अणु
	हाल 5:
		irq_bits = 0x05;
		अवरोध;
	हाल 7:
		irq_bits = 0x01;
		अवरोध;
	हाल 9:
		irq_bits = 0x02;
		अवरोध;
	हाल 10:
		irq_bits = 0x03;
		अवरोध;
	हाल 11:
		irq_bits = 0x04;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "WSS irq # %d not valid\n", chip->irq);
		जाओ __skip_resources;
	पूर्ण

	चयन (chip->dma1) अणु
	हाल 0:
		dma_bits = 0x01;
		अवरोध;
	हाल 1:
		dma_bits = 0x02;
		अवरोध;
	हाल 3:
		dma_bits = 0x03;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "WSS dma1 # %d not valid\n", chip->dma1);
		जाओ __skip_resources;
	पूर्ण

	अगर (chip->dma1 == chip->dma2) अणु
		snd_prपूर्णांकk(KERN_ERR "don't want to share dmas\n");
		वापस -EBUSY;
	पूर्ण

	चयन (chip->dma2) अणु
	हाल 0:
	हाल 1:
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "WSS dma2 # %d not valid\n", chip->dma2);
		जाओ __skip_resources;
	पूर्ण
	dma_bits |= 0x04;

	spin_lock_irqsave(&chip->lock, flags);
	outb(irq_bits << 3 | dma_bits, chip->wss_base);
	spin_unlock_irqrestore(&chip->lock, flags);

__skip_resources:
	अगर (chip->hardware > OPTi9XX_HW_82C928) अणु
		चयन (chip->mpu_port) अणु
		हाल 0:
		हाल -1:
			अवरोध;
		हाल 0x300:
			mpu_port_bits = 0x03;
			अवरोध;
		हाल 0x310:
			mpu_port_bits = 0x02;
			अवरोध;
		हाल 0x320:
			mpu_port_bits = 0x01;
			अवरोध;
		हाल 0x330:
			mpu_port_bits = 0x00;
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_ERR "MPU-401 port 0x%lx not valid\n",
				   chip->mpu_port);
			जाओ __skip_mpu;
		पूर्ण

		चयन (chip->mpu_irq) अणु
		हाल 5:
			mpu_irq_bits = 0x02;
			अवरोध;
		हाल 7:
			mpu_irq_bits = 0x03;
			अवरोध;
		हाल 9:
			mpu_irq_bits = 0x00;
			अवरोध;
		हाल 10:
			mpu_irq_bits = 0x01;
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_ERR "MPU-401 irq # %d not valid\n",
				   chip->mpu_irq);
			जाओ __skip_mpu;
		पूर्ण

		snd_miro_ग_लिखो_mask(chip, OPTi9XX_MC_REG(6),
			(chip->mpu_port <= 0) ? 0x00 :
				0x80 | mpu_port_bits << 5 | mpu_irq_bits << 3,
			0xf8);
	पूर्ण
__skip_mpu:

	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_opti_check(काष्ठा snd_miro *chip)
अणु
	अचिन्हित अक्षर value;

	chip->res_mc_base = request_region(chip->mc_base, chip->mc_base_size,
					   "OPTi9xx MC");
	अगर (chip->res_mc_base == शून्य)
		वापस -ENOMEM;

	value = snd_miro_पढ़ो(chip, OPTi9XX_MC_REG(1));
	अगर (value != 0xff && value != inb(chip->mc_base + OPTi9XX_MC_REG(1)))
		अगर (value == snd_miro_पढ़ो(chip, OPTi9XX_MC_REG(1)))
			वापस 0;

	release_and_मुक्त_resource(chip->res_mc_base);
	chip->res_mc_base = शून्य;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_card_miro_detect(काष्ठा snd_card *card,
				काष्ठा snd_miro *chip)
अणु
	पूर्णांक i, err;

	क्रम (i = OPTi9XX_HW_82C929; i <= OPTi9XX_HW_82C924; i++) अणु

		अगर ((err = snd_miro_init(chip, i)) < 0)
			वापस err;

		err = snd_miro_opti_check(chip);
		अगर (err == 0)
			वापस 1;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_card_miro_aci_detect(काष्ठा snd_card *card,
				    काष्ठा snd_miro *miro)
अणु
	अचिन्हित अक्षर regval;
	पूर्णांक i;
	काष्ठा snd_miro_aci *aci = &aci_device;

	miro->aci = aci;

	mutex_init(&aci->aci_mutex);

	/* get ACI port from OPTi9xx MC 4 */

	regval=inb(miro->mc_base + 4);
	aci->aci_port = (regval & 0x10) ? 0x344 : 0x354;

	miro->res_aci_port = request_region(aci->aci_port, 3, "miro aci");
	अगर (miro->res_aci_port == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "aci i/o area 0x%lx-0x%lx already used.\n", 
			   aci->aci_port, aci->aci_port+2);
		वापस -ENOMEM;
	पूर्ण

        /* क्रमce ACI पूर्णांकo a known state */
	क्रम (i = 0; i < 3; i++)
		अगर (snd_aci_cmd(aci, ACI_ERROR_OP, -1, -1) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "can't force aci into known state.\n");
			वापस -ENXIO;
		पूर्ण

	aci->aci_venकरोr = snd_aci_cmd(aci, ACI_READ_IDCODE, -1, -1);
	aci->aci_product = snd_aci_cmd(aci, ACI_READ_IDCODE, -1, -1);
	अगर (aci->aci_venकरोr < 0 || aci->aci_product < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "can't read aci id on 0x%lx.\n",
			   aci->aci_port);
		वापस -ENXIO;
	पूर्ण

	aci->aci_version = snd_aci_cmd(aci, ACI_READ_VERSION, -1, -1);
	अगर (aci->aci_version < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "can't read aci version on 0x%lx.\n", 
			   aci->aci_port);
		वापस -ENXIO;
	पूर्ण

	अगर (snd_aci_cmd(aci, ACI_INIT, -1, -1) < 0 ||
	    snd_aci_cmd(aci, ACI_ERROR_OP, ACI_ERROR_OP, ACI_ERROR_OP) < 0 ||
	    snd_aci_cmd(aci, ACI_ERROR_OP, ACI_ERROR_OP, ACI_ERROR_OP) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "can't initialize aci.\n"); 
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_card_miro_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_miro *miro = card->निजी_data;

	release_and_मुक्त_resource(miro->res_aci_port);
	अगर (miro->aci)
		miro->aci->aci_port = 0;
	release_and_मुक्त_resource(miro->res_mc_base);
पूर्ण

अटल पूर्णांक snd_miro_probe(काष्ठा snd_card *card)
अणु
	पूर्णांक error;
	काष्ठा snd_miro *miro = card->निजी_data;
	काष्ठा snd_wss *codec;
	काष्ठा snd_rawmidi *rmidi;

	अगर (!miro->res_mc_base) अणु
		miro->res_mc_base = request_region(miro->mc_base,
						miro->mc_base_size,
						"miro (OPTi9xx MC)");
		अगर (miro->res_mc_base == शून्य) अणु
			snd_prपूर्णांकk(KERN_ERR "request for OPTI9xx MC failed\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	error = snd_card_miro_aci_detect(card, miro);
	अगर (error < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to detect aci chip\n");
		वापस -ENODEV;
	पूर्ण

	miro->wss_base = port;
	miro->mpu_port = mpu_port;
	miro->irq = irq;
	miro->mpu_irq = mpu_irq;
	miro->dma1 = dma1;
	miro->dma2 = dma2;

	/* init proc पूर्णांकerface */
	snd_miro_proc_init(card, miro);

	error = snd_miro_configure(miro);
	अगर (error)
		वापस error;

	error = snd_wss_create(card, miro->wss_base + 4, -1,
			       miro->irq, miro->dma1, miro->dma2,
			       WSS_HW_DETECT, 0, &codec);
	अगर (error < 0)
		वापस error;

	error = snd_wss_pcm(codec, 0);
	अगर (error < 0)
		वापस error;

	error = snd_wss_mixer(codec);
	अगर (error < 0)
		वापस error;

	error = snd_wss_समयr(codec, 0);
	अगर (error < 0)
		वापस error;

	miro->pcm = codec->pcm;

	error = snd_miro_mixer(card, miro);
	अगर (error < 0)
		वापस error;

	अगर (miro->aci->aci_venकरोr == 'm') अणु
		/* It looks like a miro sound card. */
		चयन (miro->aci->aci_product) अणु
		हाल 'A':
			प्र_लिखो(card->लघुname, 
				"miroSOUND PCM1 pro / PCM12");
			अवरोध;
		हाल 'B':
			प्र_लिखो(card->लघुname, 
				"miroSOUND PCM12");
			अवरोध;
		हाल 'C':
			प्र_लिखो(card->लघुname, 
				"miroSOUND PCM20 radio");
			अवरोध;
		शेष:
			प्र_लिखो(card->लघुname, 
				"unknown miro");
			snd_prपूर्णांकk(KERN_INFO "unknown miro aci id\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_prपूर्णांकk(KERN_INFO "found unsupported aci card\n");
		प्र_लिखो(card->लघुname, "unknown Cardinal Technologies");
	पूर्ण

	म_नकल(card->driver, "miro");
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s: OPTi%s, %s at 0x%lx, irq %d, dma %d&%d",
		 card->लघुname, miro->name, codec->pcm->name,
		 miro->wss_base + 4, miro->irq, miro->dma1, miro->dma2);

	अगर (mpu_port <= 0 || mpu_port == SNDRV_AUTO_PORT)
		rmidi = शून्य;
	अन्यथा अणु
		error = snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
				mpu_port, 0, miro->mpu_irq, &rmidi);
		अगर (error < 0)
			snd_prपूर्णांकk(KERN_WARNING "no MPU-401 device at 0x%lx?\n",
				   mpu_port);
	पूर्ण

	अगर (fm_port > 0 && fm_port != SNDRV_AUTO_PORT) अणु
		काष्ठा snd_opl3 *opl3 = शून्य;
		काष्ठा snd_opl4 *opl4;

		अगर (snd_opl4_create(card, fm_port, fm_port - 8,
				    2, &opl3, &opl4) < 0)
			snd_prपूर्णांकk(KERN_WARNING "no OPL4 device at 0x%lx\n",
				   fm_port);
	पूर्ण

	error = snd_set_aci_init_values(miro);
	अगर (error < 0)
                वापस error;

	वापस snd_card_रेजिस्टर(card);
पूर्ण

अटल पूर्णांक snd_miro_isa_match(काष्ठा device *devptr, अचिन्हित पूर्णांक n)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (snd_miro_pnp_is_probed)
		वापस 0;
	अगर (isapnp)
		वापस 0;
#पूर्ण_अगर
	वापस 1;
पूर्ण

अटल पूर्णांक snd_miro_isa_probe(काष्ठा device *devptr, अचिन्हित पूर्णांक n)
अणु
	अटल स्थिर दीर्घ possible_ports[] = अणु0x530, 0xe80, 0xf40, 0x604, -1पूर्ण;
	अटल स्थिर दीर्घ possible_mpu_ports[] = अणु0x330, 0x300, 0x310, 0x320, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु11, 9, 10, 7, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_mpu_irqs[] = अणु10, 5, 9, 7, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dma1s[] = अणु3, 1, 0, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dma2s[][2] = अणु अणु1, -1पूर्ण, अणु0, -1पूर्ण, अणु-1, -1पूर्ण,
					   अणु0, -1पूर्ण पूर्ण;

	पूर्णांक error;
	काष्ठा snd_miro *miro;
	काष्ठा snd_card *card;

	error = snd_card_new(devptr, index, id, THIS_MODULE,
			     माप(काष्ठा snd_miro), &card);
	अगर (error < 0)
		वापस error;

	card->निजी_मुक्त = snd_card_miro_मुक्त;
	miro = card->निजी_data;

	error = snd_card_miro_detect(card, miro);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		snd_prपूर्णांकk(KERN_ERR "unable to detect OPTi9xx chip\n");
		वापस -ENODEV;
	पूर्ण

	अगर (port == SNDRV_AUTO_PORT) अणु
		port = snd_legacy_find_मुक्त_ioport(possible_ports, 4);
		अगर (port < 0) अणु
			snd_card_मुक्त(card);
			snd_prपूर्णांकk(KERN_ERR "unable to find a free WSS port\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (mpu_port == SNDRV_AUTO_PORT) अणु
		mpu_port = snd_legacy_find_मुक्त_ioport(possible_mpu_ports, 2);
		अगर (mpu_port < 0) अणु
			snd_card_मुक्त(card);
			snd_prपूर्णांकk(KERN_ERR
				   "unable to find a free MPU401 port\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (irq == SNDRV_AUTO_IRQ) अणु
		irq = snd_legacy_find_मुक्त_irq(possible_irqs);
		अगर (irq < 0) अणु
			snd_card_मुक्त(card);
			snd_prपूर्णांकk(KERN_ERR "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (mpu_irq == SNDRV_AUTO_IRQ) अणु
		mpu_irq = snd_legacy_find_मुक्त_irq(possible_mpu_irqs);
		अगर (mpu_irq < 0) अणु
			snd_card_मुक्त(card);
			snd_prपूर्णांकk(KERN_ERR
				   "unable to find a free MPU401 IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma1 == SNDRV_AUTO_DMA) अणु
		dma1 = snd_legacy_find_मुक्त_dma(possible_dma1s);
		अगर (dma1 < 0) अणु
			snd_card_मुक्त(card);
			snd_prपूर्णांकk(KERN_ERR "unable to find a free DMA1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma2 == SNDRV_AUTO_DMA) अणु
		dma2 = snd_legacy_find_मुक्त_dma(possible_dma2s[dma1 % 4]);
		अगर (dma2 < 0) अणु
			snd_card_मुक्त(card);
			snd_prपूर्णांकk(KERN_ERR "unable to find a free DMA2\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	error = snd_miro_probe(card);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण

	dev_set_drvdata(devptr, card);
	वापस 0;
पूर्ण

अटल व्योम snd_miro_isa_हटाओ(काष्ठा device *devptr,
			       अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#घोषणा DEV_NAME "miro"

अटल काष्ठा isa_driver snd_miro_driver = अणु
	.match		= snd_miro_isa_match,
	.probe		= snd_miro_isa_probe,
	.हटाओ		= snd_miro_isa_हटाओ,
	/* FIXME: suspend/resume */
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PNP

अटल पूर्णांक snd_card_miro_pnp(काष्ठा snd_miro *chip,
			     काष्ठा pnp_card_link *card,
			     स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;
	काष्ठा pnp_dev *devmpu;
	काष्ठा pnp_dev *devmc;

	pdev = pnp_request_card_device(card, pid->devs[0].id, शून्य);
	अगर (pdev == शून्य)
		वापस -EBUSY;

	devmpu = pnp_request_card_device(card, pid->devs[1].id, शून्य);
	अगर (devmpu == शून्य)
		वापस -EBUSY;

	devmc = pnp_request_card_device(card, pid->devs[2].id, शून्य);
	अगर (devmc == शून्य)
		वापस -EBUSY;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "AUDIO pnp configure failure: %d\n", err);
		वापस err;
	पूर्ण

	err = pnp_activate_dev(devmc);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "MC pnp configure failure: %d\n",
				    err);
		वापस err;
	पूर्ण

	port = pnp_port_start(pdev, 1);
	fm_port = pnp_port_start(pdev, 2) + 8;

	/*
	 * The MC(0) is never accessed and the miroSOUND PCM20 card करोes not
	 * include it in the PnP resource range. OPTI93x include it.
	 */
	chip->mc_base = pnp_port_start(devmc, 0) - 1;
	chip->mc_base_size = pnp_port_len(devmc, 0) + 1;

	irq = pnp_irq(pdev, 0);
	dma1 = pnp_dma(pdev, 0);
	dma2 = pnp_dma(pdev, 1);

	अगर (mpu_port > 0) अणु
		err = pnp_activate_dev(devmpu);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "MPU401 pnp configure failure\n");
			mpu_port = -1;
			वापस err;
		पूर्ण
		mpu_port = pnp_port_start(devmpu, 0);
		mpu_irq = pnp_irq(devmpu, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_miro_pnp_probe(काष्ठा pnp_card_link *pcard,
			      स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;
	काष्ठा snd_miro *miro;

	अगर (snd_miro_pnp_is_probed)
		वापस -EBUSY;
	अगर (!isapnp)
		वापस -ENODEV;
	err = snd_card_new(&pcard->card->dev, index, id, THIS_MODULE,
			   माप(काष्ठा snd_miro), &card);
	अगर (err < 0)
		वापस err;

	card->निजी_मुक्त = snd_card_miro_मुक्त;
	miro = card->निजी_data;

	err = snd_card_miro_pnp(miro, pcard, pid);
	अगर (err) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	/* only miroSOUND PCM20 and PCM12 == OPTi924 */
	err = snd_miro_init(miro, OPTi9XX_HW_82C924);
	अगर (err) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_miro_opti_check(miro);
	अगर (err) अणु
		snd_prपूर्णांकk(KERN_ERR "OPTI chip not found\n");
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_miro_probe(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	snd_miro_pnp_is_probed = 1;
	वापस 0;
पूर्ण

अटल व्योम snd_miro_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
	snd_miro_pnp_is_probed = 0;
पूर्ण

अटल काष्ठा pnp_card_driver miro_pnpc_driver = अणु
	.flags		= PNP_DRIVER_RES_DISABLE,
	.name		= "miro",
	.id_table	= snd_miro_pnpids,
	.probe		= snd_miro_pnp_probe,
	.हटाओ		= snd_miro_pnp_हटाओ,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init alsa_card_miro_init(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	pnp_रेजिस्टर_card_driver(&miro_pnpc_driver);
	अगर (snd_miro_pnp_is_probed)
		वापस 0;
	pnp_unरेजिस्टर_card_driver(&miro_pnpc_driver);
#पूर्ण_अगर
	वापस isa_रेजिस्टर_driver(&snd_miro_driver, 1);
पूर्ण

अटल व्योम __निकास alsa_card_miro_निकास(व्योम)
अणु
	अगर (!snd_miro_pnp_is_probed) अणु
		isa_unरेजिस्टर_driver(&snd_miro_driver);
		वापस;
	पूर्ण
#अगर_घोषित CONFIG_PNP
	pnp_unरेजिस्टर_card_driver(&miro_pnpc_driver);
#पूर्ण_अगर
पूर्ण

module_init(alsa_card_miro_init)
module_निकास(alsa_card_miro_निकास)
