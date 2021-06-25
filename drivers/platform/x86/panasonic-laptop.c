<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Panasonic HotKey and LCD brightness control driver
 *  (C) 2004 Hiroshi Miura <miura@da-cha.org>
 *  (C) 2004 NTT DATA Intellilink Co. http://www.पूर्णांकellilink.co.jp/
 *  (C) YOKOTA Hiroshi <yokota (at) netlab. is. tsukuba. ac. jp>
 *  (C) 2004 David Bronaugh <dbronaugh>
 *  (C) 2006-2008 Harald Welte <laक्रमge@gnumonks.org>
 *
 *  derived from toshiba_acpi.c, Copyright (C) 2002-2004 John Belmonte
 *
 *---------------------------------------------------------------------------
 *
 * ChangeLog:
 *	Aug.18, 2020	Kenneth Chan <kenneth.t.chan@gmail.com>
 *		-v0.98	add platक्रमm devices क्रम firmware brightness रेजिस्टरs
 *			add support क्रम battery अक्षरging threshold (eco mode)
 *			resolve hotkey द्विगुन trigger
 *			add ग_लिखो support to mute
 *			fix sticky_key init bug
 *			fix naming of platक्रमm files क्रम consistency with other
 *			modules
 *			split MODULE_AUTHOR() by one author per macro call
 *			replace ACPI prपूर्णांकs with pr_*() macros
 *		-v0.97	add support क्रम cdघातer hardware चयन
 *		-v0.96	merge Lucina's enhancement
 *			Jan.13, 2009 Martin Lucina <mato@kotelna.sk>
 *				- add support क्रम optical driver घातer in
 *				  Y and W series
 *
 *	Sep.23, 2008	Harald Welte <laक्रमge@gnumonks.org>
 *		-v0.95	नाम driver from drivers/acpi/pcc_acpi.c to
 *			drivers/misc/panasonic-laptop.c
 *
 * 	Jul.04, 2008	Harald Welte <laक्रमge@gnumonks.org>
 * 		-v0.94	replace /proc पूर्णांकerface with device attributes
 * 			support अणुset,getपूर्णkeycode on th input device
 *
 *      Jun.27, 2008	Harald Welte <laक्रमge@gnumonks.org>
 *      	-v0.92	merge with 2.6.26-rc6 input API changes
 *      		हटाओ broken <= 2.6.15 kernel support
 *      		resolve all compiler warnings
 *      		various coding style fixes (checkpatch.pl)
 *      		add support क्रम backlight api
 *      		major code reकाष्ठाuring
 *
 * 	Dac.28, 2007	Harald Welte <laक्रमge@gnumonks.org>
 * 		-v0.91	merge with 2.6.24-rc6 ACPI changes
 *
 * 	Nov.04, 2006	Hiroshi Miura <miura@da-cha.org>
 * 		-v0.9	हटाओ warning about section reference.
 * 			हटाओ acpi_os_मुक्त
 * 			add /proc/acpi/pcc/brightness पूर्णांकerface क्रम HAL access
 * 			merge dbronaugh's enhancement
 * 			Aug.17, 2004 David Bronaugh (dbronaugh)
 *  				- Added screen brightness setting पूर्णांकerface
 *				  Thanks to FreeBSD crew (acpi_panasonic.c)
 * 				  क्रम the ideas I needed to accomplish it
 *
 *	May.29, 2006	Hiroshi Miura <miura@da-cha.org>
 *		-v0.8.4 follow to change keyinput काष्ठाure
 *			thanks Fabian Yamaguchi <भ_असल@cs.tu-berlin.de>,
 *			Jacob Bower <jacob.bower@ic.ac.uk> and
 *			Hiroshi Yokota क्रम providing solutions.
 *
 *	Oct.02, 2004	Hiroshi Miura <miura@da-cha.org>
 *		-v0.8.2	merge code of YOKOTA Hiroshi
 *					<yokota@netlab.is.tsukuba.ac.jp>.
 *			Add sticky key mode पूर्णांकerface.
 *			Refactoring acpi_pcc_generate_keyinput().
 *
 *	Sep.15, 2004	Hiroshi Miura <miura@da-cha.org>
 *		-v0.8	Generate key input event on input subप्रणाली.
 *			This is based on yet another driver written by
 *							Ryuta Nakanishi.
 *
 *	Sep.10, 2004	Hiroshi Miura <miura@da-cha.org>
 *		-v0.7	Change proc पूर्णांकerface functions using seq_file
 *			facility as same as other ACPI drivers.
 *
 *	Aug.28, 2004	Hiroshi Miura <miura@da-cha.org>
 *		-v0.6.4 Fix a silly error with status checking
 *
 *	Aug.25, 2004	Hiroshi Miura <miura@da-cha.org>
 *		-v0.6.3 replace पढ़ो_acpi_पूर्णांक by standard function
 *							acpi_evaluate_पूर्णांकeger
 *			some clean up and make smart copyright notice.
 *			fix वापस value of pcc_acpi_get_key()
 *			fix checking वापस value of acpi_bus_रेजिस्टर_driver()
 *
 *      Aug.22, 2004    David Bronaugh <dbronaugh@linuxboxen.org>
 *              -v0.6.2 Add check on ACPI data (num_sअगरr)
 *                      Coding style cleanups, better error messages/handling
 *			Fixed an off-by-one error in memory allocation
 *
 *      Aug.21, 2004    David Bronaugh <dbronaugh@linuxboxen.org>
 *              -v0.6.1 Fix a silly error with status checking
 *
 *      Aug.20, 2004    David Bronaugh <dbronaugh@linuxboxen.org>
 *              - v0.6  Correct brightness controls to reflect reality
 *                      based on inक्रमmation gleaned by Hiroshi Miura
 *                      and discussions with Hiroshi Miura
 *
 *	Aug.10, 2004	Hiroshi Miura <miura@da-cha.org>
 *		- v0.5  support LCD brightness control
 *			based on the disबंदd inक्रमmation by MEI.
 *
 *	Jul.25, 2004	Hiroshi Miura <miura@da-cha.org>
 *		- v0.4  first post version
 *		        add function to retrive SIFR
 *
 *	Jul.24, 2004	Hiroshi Miura <miura@da-cha.org>
 *		- v0.3  get proper status of hotkey
 *
 *      Jul.22, 2004	Hiroshi Miura <miura@da-cha.org>
 *		- v0.2  add HotKey handler
 *
 *      Jul.17, 2004	Hiroshi Miura <miura@da-cha.org>
 *		- v0.1  start from toshiba_acpi driver written by John Belmonte
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/backlight.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/platक्रमm_device.h>


MODULE_AUTHOR("Hiroshi Miura <miura@da-cha.org>");
MODULE_AUTHOR("David Bronaugh <dbronaugh@linuxboxen.org>");
MODULE_AUTHOR("Harald Welte <laforge@gnumonks.org>");
MODULE_AUTHOR("Martin Lucina <mato@kotelna.sk>");
MODULE_AUTHOR("Kenneth Chan <kenneth.t.chan@gmail.com>");
MODULE_DESCRIPTION("ACPI HotKey driver for Panasonic Let's Note laptops");
MODULE_LICENSE("GPL");

#घोषणा LOGPREFIX "pcc_acpi: "

/* Define ACPI PATHs */
/* Lets note hotkeys */
#घोषणा METHOD_HKEY_QUERY	"HINF"
#घोषणा METHOD_HKEY_SQTY	"SQTY"
#घोषणा METHOD_HKEY_SINF	"SINF"
#घोषणा METHOD_HKEY_SSET	"SSET"
#घोषणा METHOD_ECWR		"\\_SB.ECWR"
#घोषणा HKEY_NOTIFY		0x80
#घोषणा ECO_MODE_OFF		0x00
#घोषणा ECO_MODE_ON		0x80

#घोषणा ACPI_PCC_DRIVER_NAME	"Panasonic Laptop Support"
#घोषणा ACPI_PCC_DEVICE_NAME	"Hotkey"
#घोषणा ACPI_PCC_CLASS		"pcc"

#घोषणा ACPI_PCC_INPUT_PHYS	"panasonic/hkey0"

/* LCD_TYPEs: 0 = Normal, 1 = Semi-transparent
   ECO_MODEs: 0x03 = off, 0x83 = on
*/
क्रमागत SINF_BITS अणु SINF_NUM_BATTERIES = 0,
		 SINF_LCD_TYPE,
		 SINF_AC_MAX_BRIGHT,
		 SINF_AC_MIN_BRIGHT,
		 SINF_AC_CUR_BRIGHT,
		 SINF_DC_MAX_BRIGHT,
		 SINF_DC_MIN_BRIGHT,
		 SINF_DC_CUR_BRIGHT,
		 SINF_MUTE,
		 SINF_RESERVED,
		 SINF_ECO_MODE = 0x0A,
		 SINF_CUR_BRIGHT = 0x0D,
		 SINF_STICKY_KEY = 0x80,
	पूर्ण;
/* R1 handles SINF_AC_CUR_BRIGHT as SINF_CUR_BRIGHT, करोesn't know AC state */

अटल पूर्णांक acpi_pcc_hotkey_add(काष्ठा acpi_device *device);
अटल पूर्णांक acpi_pcc_hotkey_हटाओ(काष्ठा acpi_device *device);
अटल व्योम acpi_pcc_hotkey_notअगरy(काष्ठा acpi_device *device, u32 event);

अटल स्थिर काष्ठा acpi_device_id pcc_device_ids[] = अणु
	अणु "MAT0012", 0पूर्ण,
	अणु "MAT0013", 0पूर्ण,
	अणु "MAT0018", 0पूर्ण,
	अणु "MAT0019", 0पूर्ण,
	अणु "", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pcc_device_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_pcc_hotkey_resume(काष्ठा device *dev);
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(acpi_pcc_hotkey_pm, शून्य, acpi_pcc_hotkey_resume);

अटल काष्ठा acpi_driver acpi_pcc_driver = अणु
	.name =		ACPI_PCC_DRIVER_NAME,
	.class =	ACPI_PCC_CLASS,
	.ids =		pcc_device_ids,
	.ops =		अणु
				.add =		acpi_pcc_hotkey_add,
				.हटाओ =	acpi_pcc_hotkey_हटाओ,
				.notअगरy =	acpi_pcc_hotkey_notअगरy,
			पूर्ण,
	.drv.pm =	&acpi_pcc_hotkey_pm,
पूर्ण;

अटल स्थिर काष्ठा key_entry panasonic_keymap[] = अणु
	अणु KE_KEY, 0, अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_KEY, 1, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 2, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 3, अणु KEY_DISPLAYTOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, 4, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 5, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 6, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 7, अणु KEY_SLEEP पूर्ण पूर्ण,
	अणु KE_KEY, 8, अणु KEY_PROG1 पूर्ण पूर्ण, /* Change CPU boost */
	अणु KE_KEY, 9, अणु KEY_BATTERY पूर्ण पूर्ण,
	अणु KE_KEY, 10, अणु KEY_SUSPEND पूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

काष्ठा pcc_acpi अणु
	acpi_handle		handle;
	अचिन्हित दीर्घ		num_sअगरr;
	पूर्णांक			sticky_key;
	पूर्णांक			eco_mode;
	पूर्णांक			mute;
	पूर्णांक			ac_brightness;
	पूर्णांक			dc_brightness;
	पूर्णांक			current_brightness;
	u32			*sinf;
	काष्ठा acpi_device	*device;
	काष्ठा input_dev	*input_dev;
	काष्ठा backlight_device	*backlight;
	काष्ठा platक्रमm_device	*platक्रमm;
पूर्ण;

/* method access functions */
अटल पूर्णांक acpi_pcc_ग_लिखो_sset(काष्ठा pcc_acpi *pcc, पूर्णांक func, पूर्णांक val)
अणु
	जोड़ acpi_object in_objs[] = अणु
		अणु .पूर्णांकeger.type  = ACPI_TYPE_INTEGER,
		  .पूर्णांकeger.value = func, पूर्ण,
		अणु .पूर्णांकeger.type  = ACPI_TYPE_INTEGER,
		  .पूर्णांकeger.value = val, पूर्ण,
	पूर्ण;
	काष्ठा acpi_object_list params = अणु
		.count   = ARRAY_SIZE(in_objs),
		.poपूर्णांकer = in_objs,
	पूर्ण;
	acpi_status status = AE_OK;

	status = acpi_evaluate_object(pcc->handle, METHOD_HKEY_SSET,
				      &params, शून्य);

	वापस (status == AE_OK) ? 0 : -EIO;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_pcc_get_sqty(काष्ठा acpi_device *device)
अणु
	अचिन्हित दीर्घ दीर्घ s;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, METHOD_HKEY_SQTY,
				       शून्य, &s);
	अगर (ACPI_SUCCESS(status))
		वापस s;
	अन्यथा अणु
		pr_err("evaluation error HKEY.SQTY\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_pcc_retrieve_biosdata(काष्ठा pcc_acpi *pcc)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *hkey = शून्य;
	पूर्णांक i;

	status = acpi_evaluate_object(pcc->handle, METHOD_HKEY_SINF, शून्य,
				      &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("evaluation error HKEY.SINF\n");
		वापस 0;
	पूर्ण

	hkey = buffer.poपूर्णांकer;
	अगर (!hkey || (hkey->type != ACPI_TYPE_PACKAGE)) अणु
		pr_err("Invalid HKEY.SINF\n");
		status = AE_ERROR;
		जाओ end;
	पूर्ण

	अगर (pcc->num_sअगरr < hkey->package.count) अणु
		pr_err("SQTY reports bad SINF length\n");
		status = AE_ERROR;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < hkey->package.count; i++) अणु
		जोड़ acpi_object *element = &(hkey->package.elements[i]);
		अगर (likely(element->type == ACPI_TYPE_INTEGER)) अणु
			pcc->sinf[i] = element->पूर्णांकeger.value;
		पूर्ण अन्यथा
			pr_err("Invalid HKEY.SINF data\n");
	पूर्ण
	pcc->sinf[hkey->package.count] = -1;

end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस status == AE_OK;
पूर्ण

/* backlight API पूर्णांकerface functions */

/* This driver currently treats AC and DC brightness identical,
 * since we करोn't need to invent an पूर्णांकerface to the core ACPI
 * logic to receive events in हाल a घातer supply is plugged in
 * or हटाओd */

अटल पूर्णांक bl_get(काष्ठा backlight_device *bd)
अणु
	काष्ठा pcc_acpi *pcc = bl_get_data(bd);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस pcc->sinf[SINF_AC_CUR_BRIGHT];
पूर्ण

अटल पूर्णांक bl_set_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा pcc_acpi *pcc = bl_get_data(bd);
	पूर्णांक bright = bd->props.brightness;
	पूर्णांक rc;

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	अगर (bright < pcc->sinf[SINF_AC_MIN_BRIGHT])
		bright = pcc->sinf[SINF_AC_MIN_BRIGHT];

	अगर (bright < pcc->sinf[SINF_DC_MIN_BRIGHT])
		bright = pcc->sinf[SINF_DC_MIN_BRIGHT];

	अगर (bright < pcc->sinf[SINF_AC_MIN_BRIGHT] ||
	    bright > pcc->sinf[SINF_AC_MAX_BRIGHT])
		वापस -EINVAL;

	rc = acpi_pcc_ग_लिखो_sset(pcc, SINF_AC_CUR_BRIGHT, bright);
	अगर (rc < 0)
		वापस rc;

	वापस acpi_pcc_ग_लिखो_sset(pcc, SINF_DC_CUR_BRIGHT, bright);
पूर्ण

अटल स्थिर काष्ठा backlight_ops pcc_backlight_ops = अणु
	.get_brightness	= bl_get,
	.update_status	= bl_set_status,
पूर्ण;


/* वापसs ACPI_SUCCESS अगर methods to control optical drive are present */

अटल acpi_status check_optd_present(व्योम)
अणु
	acpi_status status = AE_OK;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, "\\_SB.STAT", &handle);
	अगर (ACPI_FAILURE(status))
		जाओ out;
	status = acpi_get_handle(शून्य, "\\_SB.FBAY", &handle);
	अगर (ACPI_FAILURE(status))
		जाओ out;
	status = acpi_get_handle(शून्य, "\\_SB.CDDI", &handle);
	अगर (ACPI_FAILURE(status))
		जाओ out;

out:
	वापस status;
पूर्ण

/* get optical driver घातer state */

अटल पूर्णांक get_optd_घातer_state(व्योम)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ state;
	पूर्णांक result;

	status = acpi_evaluate_पूर्णांकeger(शून्य, "\\_SB.STAT", शून्य, &state);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("evaluation error _SB.STAT\n");
		result = -EIO;
		जाओ out;
	पूर्ण
	चयन (state) अणु
	हाल 0: /* घातer off */
		result = 0;
		अवरोध;
	हाल 0x0f: /* घातer on */
		result = 1;
		अवरोध;
	शेष:
		result = -EIO;
		अवरोध;
	पूर्ण

out:
	वापस result;
पूर्ण

/* set optical drive घातer state */

अटल पूर्णांक set_optd_घातer_state(पूर्णांक new_state)
अणु
	पूर्णांक result;
	acpi_status status;

	result = get_optd_घातer_state();
	अगर (result < 0)
		जाओ out;
	अगर (new_state == result)
		जाओ out;

	चयन (new_state) अणु
	हाल 0: /* घातer off */
		/* Call CDDR instead, since they both call the same method
		 * जबतक CDDI takes 1 arg and we are not quite sure what it is.
		 */
		status = acpi_evaluate_object(शून्य, "\\_SB.CDDR", शून्य, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			pr_err("evaluation error _SB.CDDR\n");
			result = -EIO;
		पूर्ण
		अवरोध;
	हाल 1: /* घातer on */
		status = acpi_evaluate_object(शून्य, "\\_SB.FBAY", शून्य, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			pr_err("evaluation error _SB.FBAY\n");
			result = -EIO;
		पूर्ण
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण

out:
	वापस result;
पूर्ण


/* sysfs user पूर्णांकerface functions */

अटल sमाप_प्रकार numbatt_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", pcc->sinf[SINF_NUM_BATTERIES]);
पूर्ण

अटल sमाप_प्रकार lcdtype_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", pcc->sinf[SINF_LCD_TYPE]);
पूर्ण

अटल sमाप_प्रकार mute_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", pcc->sinf[SINF_MUTE]);
पूर्ण

अटल sमाप_प्रकार mute_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);
	पूर्णांक err, val;

	err = kstrtoपूर्णांक(buf, 0, &val);
	अगर (err)
		वापस err;
	अगर (val == 0 || val == 1) अणु
		acpi_pcc_ग_लिखो_sset(pcc, SINF_MUTE, val);
		pcc->mute = val;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार sticky_key_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", pcc->sticky_key);
पूर्ण

अटल sमाप_प्रकार sticky_key_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);
	पूर्णांक err, val;

	err = kstrtoपूर्णांक(buf, 0, &val);
	अगर (err)
		वापस err;
	अगर (val == 0 || val == 1) अणु
		acpi_pcc_ग_लिखो_sset(pcc, SINF_STICKY_KEY, val);
		pcc->sticky_key = val;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार eco_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);
	पूर्णांक result;

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	चयन (pcc->sinf[SINF_ECO_MODE]) अणु
	हाल (ECO_MODE_OFF + 3):
		result = 0;
		अवरोध;
	हाल (ECO_MODE_ON + 3):
		result = 1;
		अवरोध;
	शेष:
		result = -EIO;
		अवरोध;
	पूर्ण
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", result);
पूर्ण

अटल sमाप_प्रकार eco_mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);
	पूर्णांक err, state;

	जोड़ acpi_object param[2];
	काष्ठा acpi_object_list input;
	acpi_status status;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].पूर्णांकeger.value = 0x15;
	param[1].type = ACPI_TYPE_INTEGER;
	input.count = 2;
	input.poपूर्णांकer = param;

	err = kstrtoपूर्णांक(buf, 0, &state);
	अगर (err)
		वापस err;

	चयन (state) अणु
	हाल 0:
		param[1].पूर्णांकeger.value = ECO_MODE_OFF;
		pcc->sinf[SINF_ECO_MODE] = 0;
		pcc->eco_mode = 0;
		अवरोध;
	हाल 1:
		param[1].पूर्णांकeger.value = ECO_MODE_ON;
		pcc->sinf[SINF_ECO_MODE] = 1;
		pcc->eco_mode = 1;
		अवरोध;
	शेष:
		/* nothing to करो */
		वापस count;
	पूर्ण

	status = acpi_evaluate_object(शून्य, METHOD_ECWR,
				       &input, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("%s evaluation failed\n", METHOD_ECWR);
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार ac_brightness_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", pcc->sinf[SINF_AC_CUR_BRIGHT]);
पूर्ण

अटल sमाप_प्रकार ac_brightness_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);
	पूर्णांक err, val;

	err = kstrtoपूर्णांक(buf, 0, &val);
	अगर (err)
		वापस err;
	अगर (val >= 0 && val <= 255) अणु
		acpi_pcc_ग_लिखो_sset(pcc, SINF_AC_CUR_BRIGHT, val);
		pcc->ac_brightness = val;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार dc_brightness_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", pcc->sinf[SINF_DC_CUR_BRIGHT]);
पूर्ण

अटल sमाप_प्रकार dc_brightness_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);
	पूर्णांक err, val;

	err = kstrtoपूर्णांक(buf, 0, &val);
	अगर (err)
		वापस err;
	अगर (val >= 0 && val <= 255) अणु
		acpi_pcc_ग_लिखो_sset(pcc, SINF_DC_CUR_BRIGHT, val);
		pcc->dc_brightness = val;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार current_brightness_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);

	अगर (!acpi_pcc_retrieve_biosdata(pcc))
		वापस -EIO;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", pcc->sinf[SINF_CUR_BRIGHT]);
पूर्ण

अटल sमाप_प्रकार current_brightness_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi = to_acpi_device(dev);
	काष्ठा pcc_acpi *pcc = acpi_driver_data(acpi);
	पूर्णांक err, val;

	err = kstrtoपूर्णांक(buf, 0, &val);
	अगर (err)
		वापस err;

	अगर (val >= 0 && val <= 255) अणु
		err = acpi_pcc_ग_लिखो_sset(pcc, SINF_CUR_BRIGHT, val);
		pcc->current_brightness = val;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार cdघातer_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", get_optd_घातer_state());
पूर्ण

अटल sमाप_प्रकार cdघातer_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err, val;

	err = kstrtoपूर्णांक(buf, 10, &val);
	अगर (err)
		वापस err;
	set_optd_घातer_state(val);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(numbatt);
अटल DEVICE_ATTR_RO(lcdtype);
अटल DEVICE_ATTR_RW(mute);
अटल DEVICE_ATTR_RW(sticky_key);
अटल DEVICE_ATTR_RW(eco_mode);
अटल DEVICE_ATTR_RW(ac_brightness);
अटल DEVICE_ATTR_RW(dc_brightness);
अटल DEVICE_ATTR_RW(current_brightness);
अटल DEVICE_ATTR_RW(cdघातer);

अटल काष्ठा attribute *pcc_sysfs_entries[] = अणु
	&dev_attr_numbatt.attr,
	&dev_attr_lcdtype.attr,
	&dev_attr_mute.attr,
	&dev_attr_sticky_key.attr,
	&dev_attr_eco_mode.attr,
	&dev_attr_ac_brightness.attr,
	&dev_attr_dc_brightness.attr,
	&dev_attr_current_brightness.attr,
	&dev_attr_cdघातer.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pcc_attr_group = अणु
	.name	= शून्य,		/* put in device directory */
	.attrs	= pcc_sysfs_entries,
पूर्ण;


/* hotkey input device driver */

अटल पूर्णांक sleep_keyकरोwn_seen;
अटल व्योम acpi_pcc_generate_keyinput(काष्ठा pcc_acpi *pcc)
अणु
	काष्ठा input_dev *hotk_input_dev = pcc->input_dev;
	पूर्णांक rc;
	अचिन्हित दीर्घ दीर्घ result;

	rc = acpi_evaluate_पूर्णांकeger(pcc->handle, METHOD_HKEY_QUERY,
				   शून्य, &result);
	अगर (ACPI_FAILURE(rc)) अणु
		pr_err("error getting hotkey status\n");
		वापस;
	पूर्ण

	/* hack: some firmware sends no key करोwn क्रम sleep / hibernate */
	अगर ((result & 0xf) == 0x7 || (result & 0xf) == 0xa) अणु
		अगर (result & 0x80)
			sleep_keyकरोwn_seen = 1;
		अगर (!sleep_keyकरोwn_seen)
			sparse_keymap_report_event(hotk_input_dev,
					result & 0xf, 0x80, false);
	पूर्ण

	अगर ((result & 0xf) == 0x7 || (result & 0xf) == 0x9 || (result & 0xf) == 0xa) अणु
		अगर (!sparse_keymap_report_event(hotk_input_dev,
						result & 0xf, result & 0x80, false))
			pr_err("Unknown hotkey event: 0x%04llx\n", result);
	पूर्ण
पूर्ण

अटल व्योम acpi_pcc_hotkey_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा pcc_acpi *pcc = acpi_driver_data(device);

	चयन (event) अणु
	हाल HKEY_NOTIFY:
		acpi_pcc_generate_keyinput(pcc);
		अवरोध;
	शेष:
		/* nothing to करो */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pcc_optd_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	अगर (event != ACPI_NOTIFY_EJECT_REQUEST)
		वापस;

	set_optd_घातer_state(0);
पूर्ण

अटल पूर्णांक pcc_रेजिस्टर_optd_notअगरier(काष्ठा pcc_acpi *pcc, अक्षर *node)
अणु
	acpi_status status;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, node, &handle);

	अगर (ACPI_SUCCESS(status)) अणु
		status = acpi_install_notअगरy_handler(handle,
				ACPI_SYSTEM_NOTIFY,
				pcc_optd_notअगरy, pcc);
		अगर (ACPI_FAILURE(status))
			pr_err("Failed to register notify on %s\n", node);
	पूर्ण अन्यथा
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम pcc_unरेजिस्टर_optd_notअगरier(काष्ठा pcc_acpi *pcc, अक्षर *node)
अणु
	acpi_status status = AE_OK;
	acpi_handle handle;

	status = acpi_get_handle(शून्य, node, &handle);

	अगर (ACPI_SUCCESS(status)) अणु
		status = acpi_हटाओ_notअगरy_handler(handle,
				ACPI_SYSTEM_NOTIFY,
				pcc_optd_notअगरy);
		अगर (ACPI_FAILURE(status))
			pr_err("Error removing optd notify handler %s\n",
					node);
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_pcc_init_input(काष्ठा pcc_acpi *pcc)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = ACPI_PCC_DRIVER_NAME;
	input_dev->phys = ACPI_PCC_INPUT_PHYS;
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;

	error = sparse_keymap_setup(input_dev, panasonic_keymap, शून्य);
	अगर (error) अणु
		pr_err("Unable to setup input device keymap\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		pr_err("Unable to register input device\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	pcc->input_dev = input_dev;
	वापस 0;

 err_मुक्त_dev:
	input_मुक्त_device(input_dev);
	वापस error;
पूर्ण

/* kernel module पूर्णांकerface */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_pcc_hotkey_resume(काष्ठा device *dev)
अणु
	काष्ठा pcc_acpi *pcc;

	अगर (!dev)
		वापस -EINVAL;

	pcc = acpi_driver_data(to_acpi_device(dev));
	अगर (!pcc)
		वापस -EINVAL;

	acpi_pcc_ग_लिखो_sset(pcc, SINF_MUTE, pcc->mute);
	acpi_pcc_ग_लिखो_sset(pcc, SINF_ECO_MODE, pcc->eco_mode);
	acpi_pcc_ग_लिखो_sset(pcc, SINF_STICKY_KEY, pcc->sticky_key);
	acpi_pcc_ग_लिखो_sset(pcc, SINF_AC_CUR_BRIGHT, pcc->ac_brightness);
	acpi_pcc_ग_लिखो_sset(pcc, SINF_DC_CUR_BRIGHT, pcc->dc_brightness);
	acpi_pcc_ग_लिखो_sset(pcc, SINF_CUR_BRIGHT, pcc->current_brightness);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक acpi_pcc_hotkey_add(काष्ठा acpi_device *device)
अणु
	काष्ठा backlight_properties props;
	काष्ठा pcc_acpi *pcc;
	पूर्णांक num_sअगरr, result;

	अगर (!device)
		वापस -EINVAL;

	num_sअगरr = acpi_pcc_get_sqty(device);

	अगर (num_sअगरr < 0 || num_sअगरr > 255) अणु
		pr_err("num_sifr out of range");
		वापस -ENODEV;
	पूर्ण

	pcc = kzalloc(माप(काष्ठा pcc_acpi), GFP_KERNEL);
	अगर (!pcc) अणु
		pr_err("Couldn't allocate mem for pcc");
		वापस -ENOMEM;
	पूर्ण

	pcc->sinf = kसुस्मृति(num_sअगरr + 1, माप(u32), GFP_KERNEL);
	अगर (!pcc->sinf) अणु
		result = -ENOMEM;
		जाओ out_hotkey;
	पूर्ण

	pcc->device = device;
	pcc->handle = device->handle;
	pcc->num_sअगरr = num_sअगरr;
	device->driver_data = pcc;
	म_नकल(acpi_device_name(device), ACPI_PCC_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_PCC_CLASS);

	result = acpi_pcc_init_input(pcc);
	अगर (result) अणु
		pr_err("Error installing keyinput handler\n");
		जाओ out_sinf;
	पूर्ण

	अगर (!acpi_pcc_retrieve_biosdata(pcc)) अणु
		result = -EIO;
		pr_err("Couldn't retrieve BIOS data\n");
		जाओ out_input;
	पूर्ण
	/* initialize backlight */
	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = pcc->sinf[SINF_AC_MAX_BRIGHT];
	pcc->backlight = backlight_device_रेजिस्टर("panasonic", शून्य, pcc,
						   &pcc_backlight_ops, &props);
	अगर (IS_ERR(pcc->backlight)) अणु
		result = PTR_ERR(pcc->backlight);
		जाओ out_input;
	पूर्ण

	/* पढ़ो the initial brightness setting from the hardware */
	pcc->backlight->props.brightness = pcc->sinf[SINF_AC_CUR_BRIGHT];

	/* Reset initial sticky key mode since the hardware रेजिस्टर state is not consistent */
	acpi_pcc_ग_लिखो_sset(pcc, SINF_STICKY_KEY, 0);
	pcc->sticky_key = 0;

	pcc->eco_mode = pcc->sinf[SINF_ECO_MODE];
	pcc->mute = pcc->sinf[SINF_MUTE];
	pcc->ac_brightness = pcc->sinf[SINF_AC_CUR_BRIGHT];
	pcc->dc_brightness = pcc->sinf[SINF_DC_CUR_BRIGHT];
	pcc->current_brightness = pcc->sinf[SINF_CUR_BRIGHT];

	/* add sysfs attributes */
	result = sysfs_create_group(&device->dev.kobj, &pcc_attr_group);
	अगर (result)
		जाओ out_backlight;

	/* optical drive initialization */
	अगर (ACPI_SUCCESS(check_optd_present())) अणु
		pcc->platक्रमm = platक्रमm_device_रेजिस्टर_simple("panasonic",
			-1, शून्य, 0);
		अगर (IS_ERR(pcc->platक्रमm)) अणु
			result = PTR_ERR(pcc->platक्रमm);
			जाओ out_backlight;
		पूर्ण
		result = device_create_file(&pcc->platक्रमm->dev,
			&dev_attr_cdघातer);
		pcc_रेजिस्टर_optd_notअगरier(pcc, "\\_SB.PCI0.EHCI.ERHB.OPTD");
		अगर (result)
			जाओ out_platक्रमm;
	पूर्ण अन्यथा अणु
		pcc->platक्रमm = शून्य;
	पूर्ण

	वापस 0;

out_platक्रमm:
	platक्रमm_device_unरेजिस्टर(pcc->platक्रमm);
out_backlight:
	backlight_device_unरेजिस्टर(pcc->backlight);
out_input:
	input_unरेजिस्टर_device(pcc->input_dev);
out_sinf:
	kमुक्त(pcc->sinf);
out_hotkey:
	kमुक्त(pcc);

	वापस result;
पूर्ण

अटल पूर्णांक acpi_pcc_hotkey_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा pcc_acpi *pcc = acpi_driver_data(device);

	अगर (!device || !pcc)
		वापस -EINVAL;

	अगर (pcc->platक्रमm) अणु
		device_हटाओ_file(&pcc->platक्रमm->dev, &dev_attr_cdघातer);
		platक्रमm_device_unरेजिस्टर(pcc->platक्रमm);
	पूर्ण
	pcc_unरेजिस्टर_optd_notअगरier(pcc, "\\_SB.PCI0.EHCI.ERHB.OPTD");

	sysfs_हटाओ_group(&device->dev.kobj, &pcc_attr_group);

	backlight_device_unरेजिस्टर(pcc->backlight);

	input_unरेजिस्टर_device(pcc->input_dev);

	kमुक्त(pcc->sinf);
	kमुक्त(pcc);

	वापस 0;
पूर्ण

module_acpi_driver(acpi_pcc_driver);
