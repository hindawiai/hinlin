<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. SMU based controls
 *
 * (c) Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/completion.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/smu.h>

#समावेश "windfarm.h"

#घोषणा VERSION "0.4"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल पूर्णांक smu_supports_new_fans_ops = 1;

/*
 * SMU fans control object
 */

अटल LIST_HEAD(smu_fans);

काष्ठा smu_fan_control अणु
	काष्ठा list_head	link;
	पूर्णांक    			fan_type;	/* 0 = rpm, 1 = pwm */
	u32			reg;		/* index in SMU */
	s32			value;		/* current value */
	s32			min, max;	/* min/max values */
	काष्ठा wf_control	ctrl;
पूर्ण;
#घोषणा to_smu_fan(c) container_of(c, काष्ठा smu_fan_control, ctrl)

अटल पूर्णांक smu_set_fan(पूर्णांक pwm, u8 id, u16 value)
अणु
	काष्ठा smu_cmd cmd;
	u8 buffer[16];
	DECLARE_COMPLETION_ONSTACK(comp);
	पूर्णांक rc;

	/* Fill SMU command काष्ठाure */
	cmd.cmd = SMU_CMD_FAN_COMMAND;

	/* The SMU has an "old" and a "new" way of setting the fan speed
	 * Unक्रमtunately, I found no reliable way to know which one works
	 * on a given machine model. After some investigations it appears
	 * that MacOS X just tries the new one, and अगर it fails fallbacks
	 * to the old ones ... Ugh.
	 */
 retry:
	अगर (smu_supports_new_fans_ops) अणु
		buffer[0] = 0x30;
		buffer[1] = id;
		*((u16 *)(&buffer[2])) = value;
		cmd.data_len = 4;
	पूर्ण अन्यथा अणु
		अगर (id > 7)
			वापस -EINVAL;
		/* Fill argument buffer */
		स_रखो(buffer, 0, 16);
		buffer[0] = pwm ? 0x10 : 0x00;
		buffer[1] = 0x01 << id;
		*((u16 *)&buffer[2 + id * 2]) = value;
		cmd.data_len = 14;
	पूर्ण

	cmd.reply_len = 16;
	cmd.data_buf = cmd.reply_buf = buffer;
	cmd.status = 0;
	cmd.करोne = smu_करोne_complete;
	cmd.misc = &comp;

	rc = smu_queue_cmd(&cmd);
	अगर (rc)
		वापस rc;
	रुको_क्रम_completion(&comp);

	/* Handle fallback (see comment above) */
	अगर (cmd.status != 0 && smu_supports_new_fans_ops) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: SMU failed new fan command "
		       "falling back to old method\n");
		smu_supports_new_fans_ops = 0;
		जाओ retry;
	पूर्ण

	वापस cmd.status;
पूर्ण

अटल व्योम smu_fan_release(काष्ठा wf_control *ct)
अणु
	काष्ठा smu_fan_control *fct = to_smu_fan(ct);

	kमुक्त(fct);
पूर्ण

अटल पूर्णांक smu_fan_set(काष्ठा wf_control *ct, s32 value)
अणु
	काष्ठा smu_fan_control *fct = to_smu_fan(ct);

	अगर (value < fct->min)
		value = fct->min;
	अगर (value > fct->max)
		value = fct->max;
	fct->value = value;

	वापस smu_set_fan(fct->fan_type, fct->reg, value);
पूर्ण

अटल पूर्णांक smu_fan_get(काष्ठा wf_control *ct, s32 *value)
अणु
	काष्ठा smu_fan_control *fct = to_smu_fan(ct);
	*value = fct->value; /* toकरो: पढ़ो from SMU */
	वापस 0;
पूर्ण

अटल s32 smu_fan_min(काष्ठा wf_control *ct)
अणु
	काष्ठा smu_fan_control *fct = to_smu_fan(ct);
	वापस fct->min;
पूर्ण

अटल s32 smu_fan_max(काष्ठा wf_control *ct)
अणु
	काष्ठा smu_fan_control *fct = to_smu_fan(ct);
	वापस fct->max;
पूर्ण

अटल स्थिर काष्ठा wf_control_ops smu_fan_ops = अणु
	.set_value	= smu_fan_set,
	.get_value	= smu_fan_get,
	.get_min	= smu_fan_min,
	.get_max	= smu_fan_max,
	.release	= smu_fan_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा smu_fan_control *smu_fan_create(काष्ठा device_node *node,
					      पूर्णांक pwm_fan)
अणु
	काष्ठा smu_fan_control *fct;
	स्थिर s32 *v;
	स्थिर u32 *reg;
	स्थिर अक्षर *l;

	fct = kदो_स्मृति(माप(काष्ठा smu_fan_control), GFP_KERNEL);
	अगर (fct == शून्य)
		वापस शून्य;
	fct->ctrl.ops = &smu_fan_ops;
	l = of_get_property(node, "location", शून्य);
	अगर (l == शून्य)
		जाओ fail;

	fct->fan_type = pwm_fan;
	fct->ctrl.type = pwm_fan ? WF_CONTROL_PWM_FAN : WF_CONTROL_RPM_FAN;

	/* We use the name & location here the same way we करो क्रम SMU sensors,
	 * see the comment in windfarm_smu_sensors.c. The locations are a bit
	 * less consistent here between the iMac and the desktop models, but
	 * that is good enough क्रम our needs क्रम now at least.
	 *
	 * One problem though is that Apple seem to be inconsistent with हाल
	 * and the kernel करोesn't have strहालcmp =P
	 */

	fct->ctrl.name = शून्य;

	/* Names used on desktop models */
	अगर (!म_भेद(l, "Rear Fan 0") || !म_भेद(l, "Rear Fan") ||
	    !म_भेद(l, "Rear fan 0") || !म_भेद(l, "Rear fan") ||
	    !म_भेद(l, "CPU A EXHAUST"))
		fct->ctrl.name = "cpu-rear-fan-0";
	अन्यथा अगर (!म_भेद(l, "Rear Fan 1") || !म_भेद(l, "Rear fan 1") ||
		 !म_भेद(l, "CPU B EXHAUST"))
		fct->ctrl.name = "cpu-rear-fan-1";
	अन्यथा अगर (!म_भेद(l, "Front Fan 0") || !म_भेद(l, "Front Fan") ||
		 !म_भेद(l, "Front fan 0") || !म_भेद(l, "Front fan") ||
		 !म_भेद(l, "CPU A INTAKE"))
		fct->ctrl.name = "cpu-front-fan-0";
	अन्यथा अगर (!म_भेद(l, "Front Fan 1") || !म_भेद(l, "Front fan 1") ||
		 !म_भेद(l, "CPU B INTAKE"))
		fct->ctrl.name = "cpu-front-fan-1";
	अन्यथा अगर (!म_भेद(l, "CPU A PUMP"))
		fct->ctrl.name = "cpu-pump-0";
	अन्यथा अगर (!म_भेद(l, "CPU B PUMP"))
		fct->ctrl.name = "cpu-pump-1";
	अन्यथा अगर (!म_भेद(l, "Slots Fan") || !म_भेद(l, "Slots fan") ||
		 !म_भेद(l, "EXPANSION SLOTS INTAKE"))
		fct->ctrl.name = "slots-fan";
	अन्यथा अगर (!म_भेद(l, "Drive Bay") || !म_भेद(l, "Drive bay") ||
		 !म_भेद(l, "DRIVE BAY A INTAKE"))
		fct->ctrl.name = "drive-bay-fan";
	अन्यथा अगर (!म_भेद(l, "BACKSIDE"))
		fct->ctrl.name = "backside-fan";

	/* Names used on iMac models */
	अगर (!म_भेद(l, "System Fan") || !म_भेद(l, "System fan"))
		fct->ctrl.name = "system-fan";
	अन्यथा अगर (!म_भेद(l, "CPU Fan") || !म_भेद(l, "CPU fan"))
		fct->ctrl.name = "cpu-fan";
	अन्यथा अगर (!म_भेद(l, "Hard Drive") || !म_भेद(l, "Hard drive"))
		fct->ctrl.name = "drive-bay-fan";
	अन्यथा अगर (!म_भेद(l, "HDD Fan")) /* seen on iMac G5 iSight */
		fct->ctrl.name = "hard-drive-fan";
	अन्यथा अगर (!म_भेद(l, "ODD Fan")) /* same */
		fct->ctrl.name = "optical-drive-fan";

	/* Unrecognized fan, bail out */
	अगर (fct->ctrl.name == शून्य)
		जाओ fail;

	/* Get min & max values*/
	v = of_get_property(node, "min-value", शून्य);
	अगर (v == शून्य)
		जाओ fail;
	fct->min = *v;
	v = of_get_property(node, "max-value", शून्य);
	अगर (v == शून्य)
		जाओ fail;
	fct->max = *v;

	/* Get "reg" value */
	reg = of_get_property(node, "reg", शून्य);
	अगर (reg == शून्य)
		जाओ fail;
	fct->reg = *reg;

	अगर (wf_रेजिस्टर_control(&fct->ctrl))
		जाओ fail;

	वापस fct;
 fail:
	kमुक्त(fct);
	वापस शून्य;
पूर्ण


अटल पूर्णांक __init smu_controls_init(व्योम)
अणु
	काष्ठा device_node *smu, *fans, *fan;

	अगर (!smu_present())
		वापस -ENODEV;

	smu = of_find_node_by_type(शून्य, "smu");
	अगर (smu == शून्य)
		वापस -ENODEV;

	/* Look क्रम RPM fans */
	क्रम (fans = शून्य; (fans = of_get_next_child(smu, fans)) != शून्य;)
		अगर (of_node_name_eq(fans, "rpm-fans") ||
		    of_device_is_compatible(fans, "smu-rpm-fans"))
			अवरोध;
	क्रम (fan = शून्य;
	     fans && (fan = of_get_next_child(fans, fan)) != शून्य;) अणु
		काष्ठा smu_fan_control *fct;

		fct = smu_fan_create(fan, 0);
		अगर (fct == शून्य) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: Failed to create SMU "
			       "RPM fan %pOFn\n", fan);
			जारी;
		पूर्ण
		list_add(&fct->link, &smu_fans);
	पूर्ण
	of_node_put(fans);


	/* Look क्रम PWM fans */
	क्रम (fans = शून्य; (fans = of_get_next_child(smu, fans)) != शून्य;)
		अगर (of_node_name_eq(fans, "pwm-fans"))
			अवरोध;
	क्रम (fan = शून्य;
	     fans && (fan = of_get_next_child(fans, fan)) != शून्य;) अणु
		काष्ठा smu_fan_control *fct;

		fct = smu_fan_create(fan, 1);
		अगर (fct == शून्य) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: Failed to create SMU "
			       "PWM fan %pOFn\n", fan);
			जारी;
		पूर्ण
		list_add(&fct->link, &smu_fans);
	पूर्ण
	of_node_put(fans);
	of_node_put(smu);

	वापस 0;
पूर्ण

अटल व्योम __निकास smu_controls_निकास(व्योम)
अणु
	काष्ठा smu_fan_control *fct;

	जबतक (!list_empty(&smu_fans)) अणु
		fct = list_entry(smu_fans.next, काष्ठा smu_fan_control, link);
		list_del(&fct->link);
		wf_unरेजिस्टर_control(&fct->ctrl);
	पूर्ण
पूर्ण


module_init(smu_controls_init);
module_निकास(smu_controls_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("SMU control objects for PowerMacs thermal control");
MODULE_LICENSE("GPL");

