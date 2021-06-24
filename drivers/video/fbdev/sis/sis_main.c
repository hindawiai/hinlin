<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SiS 300/540/630[S]/730[S],
 * SiS 315[E|PRO]/550/[M]65x/[M]66x[F|M|G]X/[M]74x[GX]/330/[M]76x[GX],
 * XGI V3XT/V5/V8, Z7
 * frame buffer driver क्रम Linux kernels >= 2.4.14 and >=2.6.3
 *
 * Copyright (C) 2001-2005 Thomas Winischhofer, Vienna, Austria.
 *
 * Author:	Thomas Winischhofer <thomas@winischhofer.net>
 *
 * Author of (practically wiped) code base:
 *		SiS (www.sis.com)
 *		Copyright (C) 1999 Silicon Integrated Systems, Inc.
 *
 * See http://www.winischhofer.net/ क्रम more inक्रमmation and updates
 *
 * Originally based on the VBE 2.0 compliant graphic boards framebuffer driver,
 * which is (c) 1998 Gerd Knorr <kraxel@goldbach.in-berlin.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/selection.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#समावेश "sis.h"
#समावेश "sis_main.h"
#समावेश "init301.h"

#अगर !defined(CONFIG_FB_SIS_300) && !defined(CONFIG_FB_SIS_315)
#warning Neither CONFIG_FB_SIS_300 nor CONFIG_FB_SIS_315 is set
#warning sisfb will not work!
#पूर्ण_अगर

/* ---------------------- Prototypes ------------------------- */

/* Interface used by the world */
#अगर_अघोषित MODULE
अटल पूर्णांक sisfb_setup(अक्षर *options);
#पूर्ण_अगर

/* Interface to the low level console driver */
अटल पूर्णांक sisfb_init(व्योम);

/* fbdev routines */
अटल पूर्णांक	sisfb_get_fix(काष्ठा fb_fix_screeninfo *fix, पूर्णांक con,
				काष्ठा fb_info *info);

अटल पूर्णांक	sisfb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg);
अटल पूर्णांक	sisfb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक	sisfb_blank(पूर्णांक blank,
				काष्ठा fb_info *info);

अटल व्योम sisfb_handle_command(काष्ठा sis_video_info *ivideo,
				 काष्ठा sisfb_cmd *sisfb_command);

अटल व्योम	sisfb_search_mode(अक्षर *name, bool quiet);
अटल पूर्णांक	sisfb_validate_mode(काष्ठा sis_video_info *ivideo, पूर्णांक modeindex, u32 vbflags);
अटल u8	sisfb_search_refresh_rate(काष्ठा sis_video_info *ivideo, अचिन्हित पूर्णांक rate,
				पूर्णांक index);
अटल पूर्णांक	sisfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
				अचिन्हित blue, अचिन्हित transp,
				काष्ठा fb_info *fb_info);
अटल पूर्णांक	sisfb_करो_set_var(काष्ठा fb_var_screeninfo *var, पूर्णांक isactive,
				काष्ठा fb_info *info);
अटल व्योम	sisfb_pre_seपंचांगode(काष्ठा sis_video_info *ivideo);
अटल व्योम	sisfb_post_seपंचांगode(काष्ठा sis_video_info *ivideo);
अटल bool	sisfb_CheckVBRetrace(काष्ठा sis_video_info *ivideo);
अटल bool	sisfbcheckvretracecrt2(काष्ठा sis_video_info *ivideo);
अटल bool	sisfbcheckvretracecrt1(काष्ठा sis_video_info *ivideo);
अटल bool	sisfb_bridgeisslave(काष्ठा sis_video_info *ivideo);
अटल व्योम	sisfb_detect_VB_connect(काष्ठा sis_video_info *ivideo);
अटल व्योम	sisfb_get_VB_type(काष्ठा sis_video_info *ivideo);
अटल व्योम	sisfb_set_TVxposoffset(काष्ठा sis_video_info *ivideo, पूर्णांक val);
अटल व्योम	sisfb_set_TVyposoffset(काष्ठा sis_video_info *ivideo, पूर्णांक val);

/* Internal heap routines */
अटल पूर्णांक		sisfb_heap_init(काष्ठा sis_video_info *ivideo);
अटल काष्ठा SIS_OH *	sisfb_poh_new_node(काष्ठा SIS_HEAP *memheap);
अटल काष्ठा SIS_OH *	sisfb_poh_allocate(काष्ठा SIS_HEAP *memheap, u32 size);
अटल व्योम		sisfb_delete_node(काष्ठा SIS_OH *poh);
अटल व्योम		sisfb_insert_node(काष्ठा SIS_OH *pohList, काष्ठा SIS_OH *poh);
अटल काष्ठा SIS_OH *	sisfb_poh_मुक्त(काष्ठा SIS_HEAP *memheap, u32 base);
अटल व्योम		sisfb_मुक्त_node(काष्ठा SIS_HEAP *memheap, काष्ठा SIS_OH *poh);


/* ------------------ Internal helper routines ----------------- */

अटल व्योम __init
sisfb_setशेषparms(व्योम)
अणु
	sisfb_off		= 0;
	sisfb_parm_mem		= 0;
	sisfb_accel		= -1;
	sisfb_ypan		= -1;
	sisfb_max		= -1;
	sisfb_userom		= -1;
	sisfb_useoem		= -1;
	sisfb_mode_idx		= -1;
	sisfb_parm_rate		= -1;
	sisfb_crt1off		= 0;
	sisfb_क्रमcecrt1		= -1;
	sisfb_crt2type		= -1;
	sisfb_crt2flags		= 0;
	sisfb_pdc		= 0xff;
	sisfb_pdca		= 0xff;
	sisfb_scalelcd		= -1;
	sisfb_specialtiming 	= CUT_NONE;
	sisfb_lvdshl		= -1;
	sisfb_dstn		= 0;
	sisfb_fstn		= 0;
	sisfb_tvplug		= -1;
	sisfb_tvstd		= -1;
	sisfb_tvxposoffset	= 0;
	sisfb_tvyposoffset	= 0;
	sisfb_nocrt2rate	= 0;
#अगर !defined(__i386__) && !defined(__x86_64__)
	sisfb_resetcard		= 0;
	sisfb_videoram		= 0;
#पूर्ण_अगर
पूर्ण

/* ------------- Parameter parsing -------------- */

अटल व्योम sisfb_search_vesamode(अचिन्हित पूर्णांक vesamode, bool quiet)
अणु
	पूर्णांक i = 0, j = 0;

	/* We करोn't know the hardware specs yet and there is no ivideo */

	अगर(vesamode == 0) अणु
		अगर(!quiet)
			prपूर्णांकk(KERN_ERR "sisfb: Invalid mode. Using default.\n");

		sisfb_mode_idx = DEFAULT_MODE;

		वापस;
	पूर्ण

	vesamode &= 0x1dff;  /* Clean VESA mode number from other flags */

	जबतक(sisbios_mode[i++].mode_no[0] != 0) अणु
		अगर( (sisbios_mode[i-1].vesa_mode_no_1 == vesamode) ||
		    (sisbios_mode[i-1].vesa_mode_no_2 == vesamode) ) अणु
			अगर(sisfb_fstn) अणु
				अगर(sisbios_mode[i-1].mode_no[1] == 0x50 ||
				   sisbios_mode[i-1].mode_no[1] == 0x56 ||
				   sisbios_mode[i-1].mode_no[1] == 0x53)
					जारी;
			पूर्ण अन्यथा अणु
				अगर(sisbios_mode[i-1].mode_no[1] == 0x5a ||
				   sisbios_mode[i-1].mode_no[1] == 0x5b)
					जारी;
			पूर्ण
			sisfb_mode_idx = i - 1;
			j = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर((!j) && !quiet)
		prपूर्णांकk(KERN_ERR "sisfb: Invalid VESA mode 0x%x'\n", vesamode);
पूर्ण

अटल व्योम sisfb_search_mode(अक्षर *name, bool quiet)
अणु
	अचिन्हित पूर्णांक j = 0, xres = 0, yres = 0, depth = 0, rate = 0;
	पूर्णांक i = 0;
	अक्षर strbuf[16], strbuf1[20];
	अक्षर *nameptr = name;

	/* We करोn't know the hardware specs yet and there is no ivideo */

	अगर(name == शून्य) अणु
		अगर(!quiet)
			prपूर्णांकk(KERN_ERR "sisfb: Internal error, using default mode.\n");

		sisfb_mode_idx = DEFAULT_MODE;
		वापस;
	पूर्ण

	अगर(!strnहालcmp(name, sisbios_mode[MODE_INDEX_NONE].name, म_माप(name))) अणु
		अगर(!quiet)
			prपूर्णांकk(KERN_ERR "sisfb: Mode 'none' not supported anymore. Using default.\n");

		sisfb_mode_idx = DEFAULT_MODE;
		वापस;
	पूर्ण

	अगर(म_माप(name) <= 19) अणु
		म_नकल(strbuf1, name);
		क्रम(i = 0; i < म_माप(strbuf1); i++) अणु
			अगर(strbuf1[i] < '0' || strbuf1[i] > '9') strbuf1[i] = ' ';
		पूर्ण

		/* This करोes some fuzzy mode naming detection */
		अगर(माला_पूछो(strbuf1, "%u %u %u %u", &xres, &yres, &depth, &rate) == 4) अणु
			अगर((rate <= 32) || (depth > 32)) अणु
				j = rate; rate = depth; depth = j;
			पूर्ण
			प्र_लिखो(strbuf, "%ux%ux%u", xres, yres, depth);
			nameptr = strbuf;
			sisfb_parm_rate = rate;
		पूर्ण अन्यथा अगर(माला_पूछो(strbuf1, "%u %u %u", &xres, &yres, &depth) == 3) अणु
			प्र_लिखो(strbuf, "%ux%ux%u", xres, yres, depth);
			nameptr = strbuf;
		पूर्ण अन्यथा अणु
			xres = 0;
			अगर((माला_पूछो(strbuf1, "%u %u", &xres, &yres) == 2) && (xres != 0)) अणु
				प्र_लिखो(strbuf, "%ux%ux8", xres, yres);
				nameptr = strbuf;
			पूर्ण अन्यथा अणु
				sisfb_search_vesamode(simple_म_से_अदीर्घ(name, शून्य, 0), quiet);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	i = 0; j = 0;
	जबतक(sisbios_mode[i].mode_no[0] != 0) अणु
		अगर(!strnहालcmp(nameptr, sisbios_mode[i++].name, म_माप(nameptr))) अणु
			अगर(sisfb_fstn) अणु
				अगर(sisbios_mode[i-1].mode_no[1] == 0x50 ||
				   sisbios_mode[i-1].mode_no[1] == 0x56 ||
				   sisbios_mode[i-1].mode_no[1] == 0x53)
					जारी;
			पूर्ण अन्यथा अणु
				अगर(sisbios_mode[i-1].mode_no[1] == 0x5a ||
				   sisbios_mode[i-1].mode_no[1] == 0x5b)
					जारी;
			पूर्ण
			sisfb_mode_idx = i - 1;
			j = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर((!j) && !quiet)
		prपूर्णांकk(KERN_ERR "sisfb: Invalid mode '%s'\n", nameptr);
पूर्ण

#अगर_अघोषित MODULE
अटल व्योम sisfb_get_vga_mode_from_kernel(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	अक्षर mymode[32];
	पूर्णांक  mydepth = screen_info.lfb_depth;

	अगर(screen_info.orig_video_isVGA != VIDEO_TYPE_VLFB) वापस;

	अगर( (screen_info.lfb_width >= 320) && (screen_info.lfb_width <= 2048) &&
	    (screen_info.lfb_height >= 200) && (screen_info.lfb_height <= 1536) &&
	    (mydepth >= 8) && (mydepth <= 32) ) अणु

		अगर(mydepth == 24) mydepth = 32;

		प्र_लिखो(mymode, "%ux%ux%u", screen_info.lfb_width,
					screen_info.lfb_height,
					mydepth);

		prपूर्णांकk(KERN_DEBUG
			"sisfb: Using vga mode %s pre-set by kernel as default\n",
			mymode);

		sisfb_search_mode(mymode, true);
	पूर्ण
#पूर्ण_अगर
	वापस;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init
sisfb_search_crt2type(स्थिर अक्षर *name)
अणु
	पूर्णांक i = 0;

	/* We करोn't know the hardware specs yet and there is no ivideo */

	अगर(name == शून्य) वापस;

	जबतक(sis_crt2type[i].type_no != -1) अणु
		अगर(!strnहालcmp(name, sis_crt2type[i].name, म_माप(sis_crt2type[i].name))) अणु
			sisfb_crt2type = sis_crt2type[i].type_no;
			sisfb_tvplug = sis_crt2type[i].tvplug_no;
			sisfb_crt2flags = sis_crt2type[i].flags;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण

	sisfb_dstn = (sisfb_crt2flags & FL_550_DSTN) ? 1 : 0;
	sisfb_fstn = (sisfb_crt2flags & FL_550_FSTN) ? 1 : 0;

	अगर(sisfb_crt2type < 0)
		prपूर्णांकk(KERN_ERR "sisfb: Invalid CRT2 type: %s\n", name);
पूर्ण

अटल व्योम __init
sisfb_search_tvstd(स्थिर अक्षर *name)
अणु
	पूर्णांक i = 0;

	/* We करोn't know the hardware specs yet and there is no ivideo */

	अगर(name == शून्य)
		वापस;

	जबतक(sis_tvtype[i].type_no != -1) अणु
		अगर(!strnहालcmp(name, sis_tvtype[i].name, म_माप(sis_tvtype[i].name))) अणु
			sisfb_tvstd = sis_tvtype[i].type_no;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
पूर्ण

अटल व्योम __init
sisfb_search_specialtiming(स्थिर अक्षर *name)
अणु
	पूर्णांक i = 0;
	bool found = false;

	/* We करोn't know the hardware specs yet and there is no ivideo */

	अगर(name == शून्य)
		वापस;

	अगर(!strnहालcmp(name, "none", 4)) अणु
		sisfb_specialtiming = CUT_FORCENONE;
		prपूर्णांकk(KERN_DEBUG "sisfb: Special timing disabled\n");
	पूर्ण अन्यथा अणु
		जबतक(mycustomttable[i].chipID != 0) अणु
			अगर(!strnहालcmp(name,mycustomttable[i].optionName,
			   म_माप(mycustomttable[i].optionName))) अणु
				sisfb_specialtiming = mycustomttable[i].SpecialID;
				found = true;
				prपूर्णांकk(KERN_INFO "sisfb: Special timing for %s %s forced (\"%s\")\n",
					mycustomttable[i].venकरोrName,
					mycustomttable[i].cardName,
					mycustomttable[i].optionName);
				अवरोध;
			पूर्ण
			i++;
		पूर्ण
		अगर(!found) अणु
			prपूर्णांकk(KERN_WARNING "sisfb: Invalid SpecialTiming parameter, valid are:");
			prपूर्णांकk(KERN_WARNING "\t\"none\" (to disable special timings)\n");
			i = 0;
			जबतक(mycustomttable[i].chipID != 0) अणु
				prपूर्णांकk(KERN_WARNING "\t\"%s\" (for %s %s)\n",
					mycustomttable[i].optionName,
					mycustomttable[i].venकरोrName,
					mycustomttable[i].cardName);
				i++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* ----------- Various detection routines ----------- */

अटल व्योम sisfb_detect_custom_timing(काष्ठा sis_video_info *ivideo)
अणु
	अचिन्हित अक्षर *biosver = शून्य;
	अचिन्हित अक्षर *biosdate = शून्य;
	bool footprपूर्णांक;
	u32 chksum = 0;
	पूर्णांक i, j;

	अगर(ivideo->SiS_Pr.UseROM) अणु
		biosver = ivideo->SiS_Pr.VirtualRomBase + 0x06;
		biosdate = ivideo->SiS_Pr.VirtualRomBase + 0x2c;
		क्रम(i = 0; i < 32768; i++)
			chksum += ivideo->SiS_Pr.VirtualRomBase[i];
	पूर्ण

	i = 0;
	करो अणु
		अगर( (mycustomttable[i].chipID == ivideo->chip)			&&
		    ((!म_माप(mycustomttable[i].biosversion)) ||
		     (ivideo->SiS_Pr.UseROM &&
		      (!म_भेदन(mycustomttable[i].biosversion, biosver,
				म_माप(mycustomttable[i].biosversion)))))	&&
		    ((!म_माप(mycustomttable[i].biosdate)) ||
		     (ivideo->SiS_Pr.UseROM &&
		      (!म_भेदन(mycustomttable[i].biosdate, biosdate,
				म_माप(mycustomttable[i].biosdate)))))		&&
		    ((!mycustomttable[i].bioschksum) ||
		     (ivideo->SiS_Pr.UseROM &&
		      (mycustomttable[i].bioschksum == chksum)))		&&
		    (mycustomttable[i].pcisubsysvenकरोr == ivideo->subsysvenकरोr) &&
		    (mycustomttable[i].pcisubsyscard == ivideo->subsysdevice) ) अणु
			footprपूर्णांक = true;
			क्रम(j = 0; j < 5; j++) अणु
				अगर(mycustomttable[i].biosFootprपूर्णांकAddr[j]) अणु
					अगर(ivideo->SiS_Pr.UseROM) अणु
						अगर(ivideo->SiS_Pr.VirtualRomBase[mycustomttable[i].biosFootprपूर्णांकAddr[j]] !=
							mycustomttable[i].biosFootprपूर्णांकData[j]) अणु
							footprपूर्णांक = false;
						पूर्ण
					पूर्ण अन्यथा
						footprपूर्णांक = false;
				पूर्ण
			पूर्ण
			अगर(footprपूर्णांक) अणु
				ivideo->SiS_Pr.SiS_CustomT = mycustomttable[i].SpecialID;
				prपूर्णांकk(KERN_DEBUG "sisfb: Identified [%s %s], special timing applies\n",
					mycustomttable[i].venकरोrName,
				mycustomttable[i].cardName);
				prपूर्णांकk(KERN_DEBUG "sisfb: [specialtiming parameter name: %s]\n",
					mycustomttable[i].optionName);
				अवरोध;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण जबतक(mycustomttable[i].chipID);
पूर्ण

अटल bool sisfb_पूर्णांकerpret_edid(काष्ठा sisfb_monitor *monitor, u8 *buffer)
अणु
	पूर्णांक i, j, xres, yres, refresh, index;
	u32 emodes;

	अगर(buffer[0] != 0x00 || buffer[1] != 0xff ||
	   buffer[2] != 0xff || buffer[3] != 0xff ||
	   buffer[4] != 0xff || buffer[5] != 0xff ||
	   buffer[6] != 0xff || buffer[7] != 0x00) अणु
		prपूर्णांकk(KERN_DEBUG "sisfb: Bad EDID header\n");
		वापस false;
	पूर्ण

	अगर(buffer[0x12] != 0x01) अणु
		prपूर्णांकk(KERN_INFO "sisfb: EDID version %d not supported\n",
			buffer[0x12]);
		वापस false;
	पूर्ण

	monitor->feature = buffer[0x18];

	अगर(!(buffer[0x14] & 0x80)) अणु
		अगर(!(buffer[0x14] & 0x08)) अणु
			prपूर्णांकk(KERN_INFO
				"sisfb: WARNING: Monitor does not support separate syncs\n");
		पूर्ण
	पूर्ण

	अगर(buffer[0x13] >= 0x01) अणु
	   /* EDID V1 rev 1 and 2: Search क्रम monitor descriptor
	    * to extract ranges
	    */
	    j = 0x36;
	    क्रम(i=0; i<4; i++) अणु
	       अगर(buffer[j]     == 0x00 && buffer[j + 1] == 0x00 &&
		  buffer[j + 2] == 0x00 && buffer[j + 3] == 0xfd &&
		  buffer[j + 4] == 0x00) अणु
		  monitor->hmin = buffer[j + 7];
		  monitor->hmax = buffer[j + 8];
		  monitor->vmin = buffer[j + 5];
		  monitor->vmax = buffer[j + 6];
		  monitor->dघड़ीmax = buffer[j + 9] * 10 * 1000;
		  monitor->datavalid = true;
		  अवरोध;
	       पूर्ण
	       j += 18;
	    पूर्ण
	पूर्ण

	अगर(!monitor->datavalid) अणु
	   /* Otherwise: Get a range from the list of supported
	    * Estabished Timings. This is not entirely accurate,
	    * because fixed frequency monitors are not supported
	    * that way.
	    */
	   monitor->hmin = 65535; monitor->hmax = 0;
	   monitor->vmin = 65535; monitor->vmax = 0;
	   monitor->dघड़ीmax = 0;
	   emodes = buffer[0x23] | (buffer[0x24] << 8) | (buffer[0x25] << 16);
	   क्रम(i = 0; i < 13; i++) अणु
	      अगर(emodes & sisfb_ddcsmodes[i].mask) अणु
		 अगर(monitor->hmin > sisfb_ddcsmodes[i].h) monitor->hmin = sisfb_ddcsmodes[i].h;
		 अगर(monitor->hmax < sisfb_ddcsmodes[i].h) monitor->hmax = sisfb_ddcsmodes[i].h + 1;
		 अगर(monitor->vmin > sisfb_ddcsmodes[i].v) monitor->vmin = sisfb_ddcsmodes[i].v;
		 अगर(monitor->vmax < sisfb_ddcsmodes[i].v) monitor->vmax = sisfb_ddcsmodes[i].v;
		 अगर(monitor->dघड़ीmax < sisfb_ddcsmodes[i].d) monitor->dघड़ीmax = sisfb_ddcsmodes[i].d;
	      पूर्ण
	   पूर्ण
	   index = 0x26;
	   क्रम(i = 0; i < 8; i++) अणु
	      xres = (buffer[index] + 31) * 8;
	      चयन(buffer[index + 1] & 0xc0) अणु
		 हाल 0xc0: yres = (xres * 9) / 16; अवरोध;
		 हाल 0x80: yres = (xres * 4) /  5; अवरोध;
		 हाल 0x40: yres = (xres * 3) /  4; अवरोध;
		 शेष:   yres = xres;	    अवरोध;
	      पूर्ण
	      refresh = (buffer[index + 1] & 0x3f) + 60;
	      अगर((xres >= 640) && (yres >= 480)) अणु
		 क्रम(j = 0; j < 8; j++) अणु
		    अगर((xres == sisfb_ddcभ_शेषes[j].x) &&
		       (yres == sisfb_ddcभ_शेषes[j].y) &&
		       (refresh == sisfb_ddcभ_शेषes[j].v)) अणु
		      अगर(monitor->hmin > sisfb_ddcभ_शेषes[j].h) monitor->hmin = sisfb_ddcभ_शेषes[j].h;
		      अगर(monitor->hmax < sisfb_ddcभ_शेषes[j].h) monitor->hmax = sisfb_ddcभ_शेषes[j].h + 1;
		      अगर(monitor->vmin > sisfb_ddcsmodes[j].v) monitor->vmin = sisfb_ddcsmodes[j].v;
		      अगर(monitor->vmax < sisfb_ddcsmodes[j].v) monitor->vmax = sisfb_ddcsmodes[j].v;
		      अगर(monitor->dघड़ीmax < sisfb_ddcsmodes[j].d) monitor->dघड़ीmax = sisfb_ddcsmodes[j].d;
		    पूर्ण
		 पूर्ण
	      पूर्ण
	      index += 2;
	   पूर्ण
	   अगर((monitor->hmin <= monitor->hmax) && (monitor->vmin <= monitor->vmax)) अणु
	      monitor->datavalid = true;
	   पूर्ण
	पूर्ण

	वापस monitor->datavalid;
पूर्ण

अटल व्योम sisfb_handle_ddc(काष्ठा sis_video_info *ivideo,
			     काष्ठा sisfb_monitor *monitor, पूर्णांक crtno)
अणु
	अचिन्हित लघु temp, i, realcrtno = crtno;
	अचिन्हित अक्षर  buffer[256];

	monitor->datavalid = false;

	अगर(crtno) अणु
	   अगर(ivideo->vbflags & CRT2_LCD)      realcrtno = 1;
	   अन्यथा अगर(ivideo->vbflags & CRT2_VGA) realcrtno = 2;
	   अन्यथा वापस;
	पूर्ण

	अगर((ivideo->sisfb_crt1off) && (!crtno))
		वापस;

	temp = SiS_HandleDDC(&ivideo->SiS_Pr, ivideo->vbflags, ivideo->sisvga_engine,
				realcrtno, 0, &buffer[0], ivideo->vbflags2);
	अगर((!temp) || (temp == 0xffff)) अणु
	   prपूर्णांकk(KERN_INFO "sisfb: CRT%d DDC probing failed\n", crtno + 1);
	   वापस;
	पूर्ण अन्यथा अणु
	   prपूर्णांकk(KERN_INFO "sisfb: CRT%d DDC supported\n", crtno + 1);
	   prपूर्णांकk(KERN_INFO "sisfb: CRT%d DDC level: %s%s%s%s\n",
		crtno + 1,
		(temp & 0x1a) ? "" : "[none of the supported]",
		(temp & 0x02) ? "2 " : "",
		(temp & 0x08) ? "D&P" : "",
		(temp & 0x10) ? "FPDI-2" : "");
	   अगर(temp & 0x02) अणु
	      i = 3;  /* Number of retrys */
	      करो अणु
		 temp = SiS_HandleDDC(&ivideo->SiS_Pr, ivideo->vbflags, ivideo->sisvga_engine,
				     realcrtno, 1, &buffer[0], ivideo->vbflags2);
	      पूर्ण जबतक((temp) && i--);
	      अगर(!temp) अणु
		 अगर(sisfb_पूर्णांकerpret_edid(monitor, &buffer[0])) अणु
		    prपूर्णांकk(KERN_INFO "sisfb: Monitor range H %d-%dKHz, V %d-%dHz, Max. dotclock %dMHz\n",
			monitor->hmin, monitor->hmax, monitor->vmin, monitor->vmax,
			monitor->dघड़ीmax / 1000);
		 पूर्ण अन्यथा अणु
		    prपूर्णांकk(KERN_INFO "sisfb: CRT%d DDC EDID corrupt\n", crtno + 1);
		 पूर्ण
	      पूर्ण अन्यथा अणु
		 prपूर्णांकk(KERN_INFO "sisfb: CRT%d DDC reading failed\n", crtno + 1);
	      पूर्ण
	   पूर्ण अन्यथा अणु
	      prपूर्णांकk(KERN_INFO "sisfb: VESA D&P and FPDI-2 not supported yet\n");
	   पूर्ण
	पूर्ण
पूर्ण

/* -------------- Mode validation --------------- */

अटल bool
sisfb_verअगरy_rate(काष्ठा sis_video_info *ivideo, काष्ठा sisfb_monitor *monitor,
		पूर्णांक mode_idx, पूर्णांक rate_idx, पूर्णांक rate)
अणु
	पूर्णांक htotal, vtotal;
	अचिन्हित पूर्णांक dघड़ी, hsync;

	अगर(!monitor->datavalid)
		वापस true;

	अगर(mode_idx < 0)
		वापस false;

	/* Skip क्रम 320x200, 320x240, 640x400 */
	चयन(sisbios_mode[mode_idx].mode_no[ivideo->mni]) अणु
	हाल 0x59:
	हाल 0x41:
	हाल 0x4f:
	हाल 0x50:
	हाल 0x56:
	हाल 0x53:
	हाल 0x2f:
	हाल 0x5d:
	हाल 0x5e:
		वापस true;
#अगर_घोषित CONFIG_FB_SIS_315
	हाल 0x5a:
	हाल 0x5b:
		अगर(ivideo->sisvga_engine == SIS_315_VGA) वापस true;
#पूर्ण_अगर
	पूर्ण

	अगर(rate < (monitor->vmin - 1))
		वापस false;
	अगर(rate > (monitor->vmax + 1))
		वापस false;

	अगर(sisfb_gettotalfrommode(&ivideo->SiS_Pr,
				  sisbios_mode[mode_idx].mode_no[ivideo->mni],
				  &htotal, &vtotal, rate_idx)) अणु
		dघड़ी = (htotal * vtotal * rate) / 1000;
		अगर(dघड़ी > (monitor->dघड़ीmax + 1000))
			वापस false;
		hsync = dघड़ी / htotal;
		अगर(hsync < (monitor->hmin - 1))
			वापस false;
		अगर(hsync > (monitor->hmax + 1))
			वापस false;
        पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक
sisfb_validate_mode(काष्ठा sis_video_info *ivideo, पूर्णांक myindex, u32 vbflags)
अणु
	u16 xres=0, yres, myres;

#अगर_घोषित CONFIG_FB_SIS_300
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		अगर(!(sisbios_mode[myindex].chipset & MD_SIS300))
			वापस -1 ;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
	अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
		अगर(!(sisbios_mode[myindex].chipset & MD_SIS315))
			वापस -1;
	पूर्ण
#पूर्ण_अगर

	myres = sisbios_mode[myindex].yres;

	चयन(vbflags & VB_DISPTYPE_DISP2) अणु

	हाल CRT2_LCD:
		xres = ivideo->lcdxres; yres = ivideo->lcdyres;

		अगर((ivideo->SiS_Pr.SiS_CustomT != CUT_PANEL848) &&
		   (ivideo->SiS_Pr.SiS_CustomT != CUT_PANEL856)) अणु
			अगर(sisbios_mode[myindex].xres > xres)
				वापस -1;
			अगर(myres > yres)
				वापस -1;
		पूर्ण

		अगर(ivideo->sisfb_fstn) अणु
			अगर(sisbios_mode[myindex].xres == 320) अणु
				अगर(myres == 240) अणु
					चयन(sisbios_mode[myindex].mode_no[1]) अणु
						हाल 0x50: myindex = MODE_FSTN_8;  अवरोध;
						हाल 0x56: myindex = MODE_FSTN_16; अवरोध;
						हाल 0x53: वापस -1;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		अगर(SiS_GetModeID_LCD(ivideo->sisvga_engine, vbflags, sisbios_mode[myindex].xres,
			 	sisbios_mode[myindex].yres, 0, ivideo->sisfb_fstn,
			 	ivideo->SiS_Pr.SiS_CustomT, xres, yres, ivideo->vbflags2) < 0x14) अणु
			वापस -1;
		पूर्ण
		अवरोध;

	हाल CRT2_TV:
		अगर(SiS_GetModeID_TV(ivideo->sisvga_engine, vbflags, sisbios_mode[myindex].xres,
				sisbios_mode[myindex].yres, 0, ivideo->vbflags2) < 0x14) अणु
			वापस -1;
		पूर्ण
		अवरोध;

	हाल CRT2_VGA:
		अगर(SiS_GetModeID_VGA2(ivideo->sisvga_engine, vbflags, sisbios_mode[myindex].xres,
				sisbios_mode[myindex].yres, 0, ivideo->vbflags2) < 0x14) अणु
			वापस -1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस myindex;
पूर्ण

अटल u8
sisfb_search_refresh_rate(काष्ठा sis_video_info *ivideo, अचिन्हित पूर्णांक rate, पूर्णांक mode_idx)
अणु
	पूर्णांक i = 0;
	u16 xres = sisbios_mode[mode_idx].xres;
	u16 yres = sisbios_mode[mode_idx].yres;

	ivideo->rate_idx = 0;
	जबतक((sisfb_vrate[i].idx != 0) && (sisfb_vrate[i].xres <= xres)) अणु
		अगर((sisfb_vrate[i].xres == xres) && (sisfb_vrate[i].yres == yres)) अणु
			अगर(sisfb_vrate[i].refresh == rate) अणु
				ivideo->rate_idx = sisfb_vrate[i].idx;
				अवरोध;
			पूर्ण अन्यथा अगर(sisfb_vrate[i].refresh > rate) अणु
				अगर((sisfb_vrate[i].refresh - rate) <= 3) अणु
					DPRINTK("sisfb: Adjusting rate from %d up to %d\n",
						rate, sisfb_vrate[i].refresh);
					ivideo->rate_idx = sisfb_vrate[i].idx;
					ivideo->refresh_rate = sisfb_vrate[i].refresh;
				पूर्ण अन्यथा अगर((sisfb_vrate[i].idx != 1) &&
						((rate - sisfb_vrate[i-1].refresh) <= 2)) अणु
					DPRINTK("sisfb: Adjusting rate from %d down to %d\n",
						rate, sisfb_vrate[i-1].refresh);
					ivideo->rate_idx = sisfb_vrate[i-1].idx;
					ivideo->refresh_rate = sisfb_vrate[i-1].refresh;
				पूर्ण
				अवरोध;
			पूर्ण अन्यथा अगर((rate - sisfb_vrate[i].refresh) <= 2) अणु
				DPRINTK("sisfb: Adjusting rate from %d down to %d\n",
						rate, sisfb_vrate[i].refresh);
				ivideo->rate_idx = sisfb_vrate[i].idx;
				अवरोध;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण
	अगर(ivideo->rate_idx > 0) अणु
		वापस ivideo->rate_idx;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "sisfb: Unsupported rate %d for %dx%d\n",
				rate, xres, yres);
		वापस 0;
	पूर्ण
पूर्ण

अटल bool
sisfb_bridgeisslave(काष्ठा sis_video_info *ivideo)
अणु
	अचिन्हित अक्षर P1_00;

	अगर(!(ivideo->vbflags2 & VB2_VIDEOBRIDGE))
		वापस false;

	P1_00 = SiS_GetReg(SISPART1, 0x00);
	अगर( ((ivideo->sisvga_engine == SIS_300_VGA) && (P1_00 & 0xa0) == 0x20) ||
	    ((ivideo->sisvga_engine == SIS_315_VGA) && (P1_00 & 0x50) == 0x10) ) अणु
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल bool
sisfballowretracecrt1(काष्ठा sis_video_info *ivideo)
अणु
	u8 temp;

	temp = SiS_GetReg(SISCR, 0x17);
	अगर(!(temp & 0x80))
		वापस false;

	temp = SiS_GetReg(SISSR, 0x1f);
	अगर(temp & 0xc0)
		वापस false;

	वापस true;
पूर्ण

अटल bool
sisfbcheckvretracecrt1(काष्ठा sis_video_info *ivideo)
अणु
	अगर(!sisfballowretracecrt1(ivideo))
		वापस false;

	अगर (SiS_GetRegByte(SISINPSTAT) & 0x08)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम
sisfbरुकोretracecrt1(काष्ठा sis_video_info *ivideo)
अणु
	पूर्णांक watchकरोg;

	अगर(!sisfballowretracecrt1(ivideo))
		वापस;

	watchकरोg = 65536;
	जबतक ((!(SiS_GetRegByte(SISINPSTAT) & 0x08)) && --watchकरोg);
	watchकरोg = 65536;
	जबतक ((SiS_GetRegByte(SISINPSTAT) & 0x08) && --watchकरोg);
पूर्ण

अटल bool
sisfbcheckvretracecrt2(काष्ठा sis_video_info *ivideo)
अणु
	अचिन्हित अक्षर temp, reg;

	चयन(ivideo->sisvga_engine) अणु
	हाल SIS_300_VGA: reg = 0x25; अवरोध;
	हाल SIS_315_VGA: reg = 0x30; अवरोध;
	शेष:	  वापस false;
	पूर्ण

	temp = SiS_GetReg(SISPART1, reg);
	अगर(temp & 0x02)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool
sisfb_CheckVBRetrace(काष्ठा sis_video_info *ivideo)
अणु
	अगर(ivideo->currentvbflags & VB_DISPTYPE_DISP2) अणु
		अगर(!sisfb_bridgeisslave(ivideo)) अणु
			वापस sisfbcheckvretracecrt2(ivideo);
		पूर्ण
	पूर्ण
	वापस sisfbcheckvretracecrt1(ivideo);
पूर्ण

अटल u32
sisfb_setupvbblankflags(काष्ठा sis_video_info *ivideo, u32 *vcount, u32 *hcount)
अणु
	u8 idx, reg1, reg2, reg3, reg4;
	u32 ret = 0;

	(*vcount) = (*hcount) = 0;

	अगर((ivideo->currentvbflags & VB_DISPTYPE_DISP2) && (!(sisfb_bridgeisslave(ivideo)))) अणु

		ret |= (FB_VBLANK_HAVE_VSYNC  |
			FB_VBLANK_HAVE_HBLANK |
			FB_VBLANK_HAVE_VBLANK |
			FB_VBLANK_HAVE_VCOUNT |
			FB_VBLANK_HAVE_HCOUNT);
		चयन(ivideo->sisvga_engine) अणु
			हाल SIS_300_VGA: idx = 0x25; अवरोध;
			शेष:
			हाल SIS_315_VGA: idx = 0x30; अवरोध;
		पूर्ण
		reg1 = SiS_GetReg(SISPART1, (idx+0)); /* 30 */
		reg2 = SiS_GetReg(SISPART1, (idx+1)); /* 31 */
		reg3 = SiS_GetReg(SISPART1, (idx+2)); /* 32 */
		reg4 = SiS_GetReg(SISPART1, (idx+3)); /* 33 */
		अगर(reg1 & 0x01) ret |= FB_VBLANK_VBLANKING;
		अगर(reg1 & 0x02) ret |= FB_VBLANK_VSYNCING;
		अगर(reg4 & 0x80) ret |= FB_VBLANK_HBLANKING;
		(*vcount) = reg3 | ((reg4 & 0x70) << 4);
		(*hcount) = reg2 | ((reg4 & 0x0f) << 8);

	पूर्ण अन्यथा अगर(sisfballowretracecrt1(ivideo)) अणु

		ret |= (FB_VBLANK_HAVE_VSYNC  |
			FB_VBLANK_HAVE_VBLANK |
			FB_VBLANK_HAVE_VCOUNT |
			FB_VBLANK_HAVE_HCOUNT);
		reg1 = SiS_GetRegByte(SISINPSTAT);
		अगर(reg1 & 0x08) ret |= FB_VBLANK_VSYNCING;
		अगर(reg1 & 0x01) ret |= FB_VBLANK_VBLANKING;
		reg1 = SiS_GetReg(SISCR, 0x20);
		reg1 = SiS_GetReg(SISCR, 0x1b);
		reg2 = SiS_GetReg(SISCR, 0x1c);
		reg3 = SiS_GetReg(SISCR, 0x1d);
		(*vcount) = reg2 | ((reg3 & 0x07) << 8);
		(*hcount) = (reg1 | ((reg3 & 0x10) << 4)) << 3;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
sisfb_myblank(काष्ठा sis_video_info *ivideo, पूर्णांक blank)
अणु
	u8 sr01, sr11, sr1f, cr63=0, p2_0, p1_13;
	bool backlight = true;

	चयन(blank) अणु
		हाल FB_BLANK_UNBLANK:	/* on */
			sr01  = 0x00;
			sr11  = 0x00;
			sr1f  = 0x00;
			cr63  = 0x00;
			p2_0  = 0x20;
			p1_13 = 0x00;
			backlight = true;
			अवरोध;
		हाल FB_BLANK_NORMAL:	/* blank */
			sr01  = 0x20;
			sr11  = 0x00;
			sr1f  = 0x00;
			cr63  = 0x00;
			p2_0  = 0x20;
			p1_13 = 0x00;
			backlight = true;
			अवरोध;
		हाल FB_BLANK_VSYNC_SUSPEND:	/* no vsync */
			sr01  = 0x20;
			sr11  = 0x08;
			sr1f  = 0x80;
			cr63  = 0x40;
			p2_0  = 0x40;
			p1_13 = 0x80;
			backlight = false;
			अवरोध;
		हाल FB_BLANK_HSYNC_SUSPEND:	/* no hsync */
			sr01  = 0x20;
			sr11  = 0x08;
			sr1f  = 0x40;
			cr63  = 0x40;
			p2_0  = 0x80;
			p1_13 = 0x40;
			backlight = false;
			अवरोध;
		हाल FB_BLANK_POWERDOWN:	/* off */
			sr01  = 0x20;
			sr11  = 0x08;
			sr1f  = 0xc0;
			cr63  = 0x40;
			p2_0  = 0xc0;
			p1_13 = 0xc0;
			backlight = false;
			अवरोध;
		शेष:
			वापस 1;
	पूर्ण

	अगर(ivideo->currentvbflags & VB_DISPTYPE_CRT1) अणु

		अगर( (!ivideo->sisfb_thismonitor.datavalid) ||
		    ((ivideo->sisfb_thismonitor.datavalid) &&
		     (ivideo->sisfb_thismonitor.feature & 0xe0))) अणु

			अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
				SiS_SetRegANDOR(SISCR, ivideo->SiS_Pr.SiS_MyCR63, 0xbf, cr63);
			पूर्ण

			अगर(!(sisfb_bridgeisslave(ivideo))) अणु
				SiS_SetRegANDOR(SISSR, 0x01, ~0x20, sr01);
				SiS_SetRegANDOR(SISSR, 0x1f, 0x3f, sr1f);
			पूर्ण
		पूर्ण

	पूर्ण

	अगर(ivideo->currentvbflags & CRT2_LCD) अणु

		अगर(ivideo->vbflags2 & VB2_SISLVDSBRIDGE) अणु
			अगर(backlight) अणु
				SiS_SiS30xBLOn(&ivideo->SiS_Pr);
			पूर्ण अन्यथा अणु
				SiS_SiS30xBLOff(&ivideo->SiS_Pr);
			पूर्ण
		पूर्ण अन्यथा अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
#अगर_घोषित CONFIG_FB_SIS_315
			अगर(ivideo->vbflags2 & VB2_CHRONTEL) अणु
				अगर(backlight) अणु
					SiS_Chrontel701xBLOn(&ivideo->SiS_Pr);
				पूर्ण अन्यथा अणु
					SiS_Chrontel701xBLOff(&ivideo->SiS_Pr);
				पूर्ण
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		अगर(((ivideo->sisvga_engine == SIS_300_VGA) &&
		    (ivideo->vbflags2 & (VB2_301|VB2_30xBDH|VB2_LVDS))) ||
		   ((ivideo->sisvga_engine == SIS_315_VGA) &&
		    ((ivideo->vbflags2 & (VB2_LVDS | VB2_CHRONTEL)) == VB2_LVDS))) अणु
			SiS_SetRegANDOR(SISSR, 0x11, ~0x0c, sr11);
		पूर्ण

		अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
			अगर((ivideo->vbflags2 & VB2_30xB) &&
			   (!(ivideo->vbflags2 & VB2_30xBDH))) अणु
				SiS_SetRegANDOR(SISPART1, 0x13, 0x3f, p1_13);
			पूर्ण
		पूर्ण अन्यथा अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
			अगर((ivideo->vbflags2 & VB2_30xB) &&
			   (!(ivideo->vbflags2 & VB2_30xBDH))) अणु
				SiS_SetRegANDOR(SISPART2, 0x00, 0x1f, p2_0);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर(ivideo->currentvbflags & CRT2_VGA) अणु

		अगर(ivideo->vbflags2 & VB2_30xB) अणु
			SiS_SetRegANDOR(SISPART2, 0x00, 0x1f, p2_0);
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

/* ------------- Callbacks from init.c/init301.c  -------------- */

#अगर_घोषित CONFIG_FB_SIS_300
अचिन्हित पूर्णांक
sisfb_पढ़ो_nbridge_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg)
अणु
   काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)SiS_Pr->ivideo;
   u32 val = 0;

   pci_पढ़ो_config_dword(ivideo->nbridge, reg, &val);
   वापस (अचिन्हित पूर्णांक)val;
पूर्ण

व्योम
sisfb_ग_लिखो_nbridge_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
   काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)SiS_Pr->ivideo;

   pci_ग_लिखो_config_dword(ivideo->nbridge, reg, (u32)val);
पूर्ण

अचिन्हित पूर्णांक
sisfb_पढ़ो_lpc_pci_dword(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg)
अणु
   काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)SiS_Pr->ivideo;
   u32 val = 0;

   अगर(!ivideo->lpcdev) वापस 0;

   pci_पढ़ो_config_dword(ivideo->lpcdev, reg, &val);
   वापस (अचिन्हित पूर्णांक)val;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
व्योम
sisfb_ग_लिखो_nbridge_pci_byte(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg, अचिन्हित अक्षर val)
अणु
   काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)SiS_Pr->ivideo;

   pci_ग_लिखो_config_byte(ivideo->nbridge, reg, (u8)val);
पूर्ण

अचिन्हित पूर्णांक
sisfb_पढ़ो_mio_pci_word(काष्ठा SiS_Private *SiS_Pr, पूर्णांक reg)
अणु
   काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)SiS_Pr->ivideo;
   u16 val = 0;

   अगर(!ivideo->lpcdev) वापस 0;

   pci_पढ़ो_config_word(ivideo->lpcdev, reg, &val);
   वापस (अचिन्हित पूर्णांक)val;
पूर्ण
#पूर्ण_अगर

/* ----------- FBDev related routines क्रम all series ----------- */

अटल पूर्णांक
sisfb_get_cmap_len(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	वापस (var->bits_per_pixel == 8) ? 256 : 16;
पूर्ण

अटल व्योम
sisfb_set_vparms(काष्ठा sis_video_info *ivideo)
अणु
	चयन(ivideo->video_bpp) अणु
	हाल 8:
		ivideo->DstColor = 0x0000;
		ivideo->SiS310_AccelDepth = 0x00000000;
		ivideo->video_cmap_len = 256;
		अवरोध;
	हाल 16:
		ivideo->DstColor = 0x8000;
		ivideo->SiS310_AccelDepth = 0x00010000;
		ivideo->video_cmap_len = 16;
		अवरोध;
	हाल 32:
		ivideo->DstColor = 0xC000;
		ivideo->SiS310_AccelDepth = 0x00020000;
		ivideo->video_cmap_len = 16;
		अवरोध;
	शेष:
		ivideo->video_cmap_len = 16;
		prपूर्णांकk(KERN_ERR "sisfb: Unsupported depth %d", ivideo->video_bpp);
		ivideo->accel = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
sisfb_calc_maxyres(काष्ठा sis_video_info *ivideo, काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक maxyres = ivideo->sisfb_mem / (var->xres_भव * (var->bits_per_pixel >> 3));

	अगर(maxyres > 32767) maxyres = 32767;

	वापस maxyres;
पूर्ण

अटल व्योम
sisfb_calc_pitch(काष्ठा sis_video_info *ivideo, काष्ठा fb_var_screeninfo *var)
अणु
	ivideo->video_linelength = var->xres_भव * (var->bits_per_pixel >> 3);
	ivideo->scrnpitchCRT1 = ivideo->video_linelength;
	अगर(!(ivideo->currentvbflags & CRT1_LCDA)) अणु
		अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
			ivideo->scrnpitchCRT1 <<= 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
sisfb_set_pitch(काष्ठा sis_video_info *ivideo)
अणु
	bool isslavemode = false;
	अचिन्हित लघु HDisplay1 = ivideo->scrnpitchCRT1 >> 3;
	अचिन्हित लघु HDisplay2 = ivideo->video_linelength >> 3;

	अगर(sisfb_bridgeisslave(ivideo)) isslavemode = true;

	/* We need to set pitch क्रम CRT1 अगर bridge is in slave mode, too */
	अगर((ivideo->currentvbflags & VB_DISPTYPE_DISP1) || (isslavemode)) अणु
		SiS_SetReg(SISCR, 0x13, (HDisplay1 & 0xFF));
		SiS_SetRegANDOR(SISSR, 0x0E, 0xF0, (HDisplay1 >> 8));
	पूर्ण

	/* We must not set the pitch क्रम CRT2 अगर bridge is in slave mode */
	अगर((ivideo->currentvbflags & VB_DISPTYPE_DISP2) && (!isslavemode)) अणु
		SiS_SetRegOR(SISPART1, ivideo->CRT2_ग_लिखो_enable, 0x01);
		SiS_SetReg(SISPART1, 0x07, (HDisplay2 & 0xFF));
		SiS_SetRegANDOR(SISPART1, 0x09, 0xF0, (HDisplay2 >> 8));
	पूर्ण
पूर्ण

अटल व्योम
sisfb_bpp_to_var(काष्ठा sis_video_info *ivideo, काष्ठा fb_var_screeninfo *var)
अणु
	ivideo->video_cmap_len = sisfb_get_cmap_len(var);

	चयन(var->bits_per_pixel) अणु
	हाल 8:
		var->red.offset = var->green.offset = var->blue.offset = 0;
		var->red.length = var->green.length = var->blue.length = 8;
		अवरोध;
	हाल 16:
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 32:
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
sisfb_set_mode(काष्ठा sis_video_info *ivideo, पूर्णांक clrscrn)
अणु
	अचिन्हित लघु modeno = ivideo->mode_no;

	/* >=2.6.12's fbcon clears the screen anyway */
	modeno |= 0x80;

	SiS_SetReg(SISSR, IND_SIS_PASSWORD, SIS_PASSWORD);

	sisfb_pre_seपंचांगode(ivideo);

	अगर(!SiSSetMode(&ivideo->SiS_Pr, modeno)) अणु
		prपूर्णांकk(KERN_ERR "sisfb: Setting mode[0x%x] failed\n", ivideo->mode_no);
		वापस -EINVAL;
	पूर्ण

	SiS_SetReg(SISSR, IND_SIS_PASSWORD, SIS_PASSWORD);

	sisfb_post_seपंचांगode(ivideo);

	वापस 0;
पूर्ण


अटल पूर्णांक
sisfb_करो_set_var(काष्ठा fb_var_screeninfo *var, पूर्णांक isactive, काष्ठा fb_info *info)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;
	अचिन्हित पूर्णांक htotal = 0, vtotal = 0;
	अचिन्हित पूर्णांक drate = 0, hrate = 0;
	पूर्णांक found_mode = 0, ret;
	पूर्णांक old_mode;
	u32 pixघड़ी;

	htotal = var->left_margin + var->xres + var->right_margin + var->hsync_len;

	vtotal = var->upper_margin + var->lower_margin + var->vsync_len;

	pixघड़ी = var->pixघड़ी;

	अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED) अणु
		vtotal += var->yres;
		vtotal <<= 1;
	पूर्ण अन्यथा अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE) अणु
		vtotal += var->yres;
		vtotal <<= 2;
	पूर्ण अन्यथा अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
		vtotal += var->yres;
		vtotal <<= 1;
	पूर्ण अन्यथा 	vtotal += var->yres;

	अगर(!(htotal) || !(vtotal)) अणु
		DPRINTK("sisfb: Invalid 'var' information\n");
		वापस -EINVAL;
	पूर्ण

	अगर(pixघड़ी && htotal && vtotal) अणु
		drate = 1000000000 / pixघड़ी;
		hrate = (drate * 1000) / htotal;
		ivideo->refresh_rate = (अचिन्हित पूर्णांक) (hrate * 2 / vtotal);
	पूर्ण अन्यथा अणु
		ivideo->refresh_rate = 60;
	पूर्ण

	old_mode = ivideo->sisfb_mode_idx;
	ivideo->sisfb_mode_idx = 0;

	जबतक( (sisbios_mode[ivideo->sisfb_mode_idx].mode_no[0] != 0) &&
	       (sisbios_mode[ivideo->sisfb_mode_idx].xres <= var->xres) ) अणु
		अगर( (sisbios_mode[ivideo->sisfb_mode_idx].xres == var->xres) &&
		    (sisbios_mode[ivideo->sisfb_mode_idx].yres == var->yres) &&
		    (sisbios_mode[ivideo->sisfb_mode_idx].bpp == var->bits_per_pixel)) अणु
			ivideo->mode_no = sisbios_mode[ivideo->sisfb_mode_idx].mode_no[ivideo->mni];
			found_mode = 1;
			अवरोध;
		पूर्ण
		ivideo->sisfb_mode_idx++;
	पूर्ण

	अगर(found_mode) अणु
		ivideo->sisfb_mode_idx = sisfb_validate_mode(ivideo,
				ivideo->sisfb_mode_idx, ivideo->currentvbflags);
	पूर्ण अन्यथा अणु
		ivideo->sisfb_mode_idx = -1;
	पूर्ण

       	अगर(ivideo->sisfb_mode_idx < 0) अणु
		prपूर्णांकk(KERN_ERR "sisfb: Mode %dx%dx%d not supported\n", var->xres,
		       var->yres, var->bits_per_pixel);
		ivideo->sisfb_mode_idx = old_mode;
		वापस -EINVAL;
	पूर्ण

	ivideo->mode_no = sisbios_mode[ivideo->sisfb_mode_idx].mode_no[ivideo->mni];

	अगर(sisfb_search_refresh_rate(ivideo, ivideo->refresh_rate, ivideo->sisfb_mode_idx) == 0) अणु
		ivideo->rate_idx = sisbios_mode[ivideo->sisfb_mode_idx].rate_idx;
		ivideo->refresh_rate = 60;
	पूर्ण

	अगर(isactive) अणु
		/* If acceleration to be used? Need to know
		 * beक्रमe pre/post_set_mode()
		 */
		ivideo->accel = 0;
#अगर defined(FBINFO_HWACCEL_DISABLED) && defined(FBINFO_HWACCEL_XPAN)
#अगर_घोषित STUPID_ACCELF_TEXT_SHIT
		अगर(var->accel_flags & FB_ACCELF_TEXT) अणु
			info->flags &= ~FBINFO_HWACCEL_DISABLED;
		पूर्ण अन्यथा अणु
			info->flags |= FBINFO_HWACCEL_DISABLED;
		पूर्ण
#पूर्ण_अगर
		अगर(!(info->flags & FBINFO_HWACCEL_DISABLED)) ivideo->accel = -1;
#अन्यथा
		अगर(var->accel_flags & FB_ACCELF_TEXT) ivideo->accel = -1;
#पूर्ण_अगर

		अगर((ret = sisfb_set_mode(ivideo, 1))) अणु
			वापस ret;
		पूर्ण

		ivideo->video_bpp    = sisbios_mode[ivideo->sisfb_mode_idx].bpp;
		ivideo->video_width  = sisbios_mode[ivideo->sisfb_mode_idx].xres;
		ivideo->video_height = sisbios_mode[ivideo->sisfb_mode_idx].yres;

		sisfb_calc_pitch(ivideo, var);
		sisfb_set_pitch(ivideo);

		sisfb_set_vparms(ivideo);

		ivideo->current_width = ivideo->video_width;
		ivideo->current_height = ivideo->video_height;
		ivideo->current_bpp = ivideo->video_bpp;
		ivideo->current_htotal = htotal;
		ivideo->current_vtotal = vtotal;
		ivideo->current_linelength = ivideo->video_linelength;
		ivideo->current_pixघड़ी = var->pixघड़ी;
		ivideo->current_refresh_rate = ivideo->refresh_rate;
		ivideo->sisfb_lastrates[ivideo->mode_no] = ivideo->refresh_rate;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
sisfb_set_base_CRT1(काष्ठा sis_video_info *ivideo, अचिन्हित पूर्णांक base)
अणु
	SiS_SetReg(SISSR, IND_SIS_PASSWORD, SIS_PASSWORD);

	SiS_SetReg(SISCR, 0x0D, base & 0xFF);
	SiS_SetReg(SISCR, 0x0C, (base >> 8) & 0xFF);
	SiS_SetReg(SISSR, 0x0D, (base >> 16) & 0xFF);
	अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
		SiS_SetRegANDOR(SISSR, 0x37, 0xFE, (base >> 24) & 0x01);
	पूर्ण
पूर्ण

अटल व्योम
sisfb_set_base_CRT2(काष्ठा sis_video_info *ivideo, अचिन्हित पूर्णांक base)
अणु
	अगर(ivideo->currentvbflags & VB_DISPTYPE_DISP2) अणु
		SiS_SetRegOR(SISPART1, ivideo->CRT2_ग_लिखो_enable, 0x01);
		SiS_SetReg(SISPART1, 0x06, (base & 0xFF));
		SiS_SetReg(SISPART1, 0x05, ((base >> 8) & 0xFF));
		SiS_SetReg(SISPART1, 0x04, ((base >> 16) & 0xFF));
		अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
			SiS_SetRegANDOR(SISPART1, 0x02, 0x7F, ((base >> 24) & 0x01) << 7);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
sisfb_pan_var(काष्ठा sis_video_info *ivideo, काष्ठा fb_info *info,
	      काष्ठा fb_var_screeninfo *var)
अणु
	ivideo->current_base = var->yoffset * info->var.xres_भव
			     + var->xoffset;

	/* calculate base bpp dep. */
	चयन (info->var.bits_per_pixel) अणु
	हाल 32:
		अवरोध;
	हाल 16:
		ivideo->current_base >>= 1;
		अवरोध;
	हाल 8:
	शेष:
		ivideo->current_base >>= 2;
		अवरोध;
	पूर्ण

	ivideo->current_base += (ivideo->video_offset >> 2);

	sisfb_set_base_CRT1(ivideo, ivideo->current_base);
	sisfb_set_base_CRT2(ivideo, ivideo->current_base);

	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green, अचिन्हित blue,
		अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;

	अगर(regno >= sisfb_get_cmap_len(&info->var))
		वापस 1;

	चयन(info->var.bits_per_pixel) अणु
	हाल 8:
		SiS_SetRegByte(SISDACA, regno);
		SiS_SetRegByte(SISDACD, (red >> 10));
		SiS_SetRegByte(SISDACD, (green >> 10));
		SiS_SetRegByte(SISDACD, (blue >> 10));
		अगर(ivideo->currentvbflags & VB_DISPTYPE_DISP2) अणु
			SiS_SetRegByte(SISDAC2A, regno);
			SiS_SetRegByte(SISDAC2D, (red >> 8));
			SiS_SetRegByte(SISDAC2D, (green >> 8));
			SiS_SetRegByte(SISDAC2D, (blue >> 8));
		पूर्ण
		अवरोध;
	हाल 16:
		अगर (regno >= 16)
			अवरोध;

		((u32 *)(info->pseuकरो_palette))[regno] =
				(red & 0xf800)          |
				((green & 0xfc00) >> 5) |
				((blue & 0xf800) >> 11);
		अवरोध;
	हाल 32:
		अगर (regno >= 16)
			अवरोध;

		red >>= 8;
		green >>= 8;
		blue >>= 8;
		((u32 *)(info->pseuकरो_palette))[regno] =
				(red << 16) | (green << 8) | (blue);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_set_par(काष्ठा fb_info *info)
अणु
	पूर्णांक err;

	अगर((err = sisfb_करो_set_var(&info->var, 1, info)))
		वापस err;

	sisfb_get_fix(&info->fix, -1, info);

	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;
	अचिन्हित पूर्णांक htotal = 0, vtotal = 0, myrateindex = 0;
	अचिन्हित पूर्णांक drate = 0, hrate = 0, maxyres;
	पूर्णांक found_mode = 0;
	पूर्णांक refresh_rate, search_idx, tidx;
	bool recalc_घड़ी = false;
	u32 pixघड़ी;

	htotal = var->left_margin + var->xres + var->right_margin + var->hsync_len;

	vtotal = var->upper_margin + var->lower_margin + var->vsync_len;

	pixघड़ी = var->pixघड़ी;

	अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED) अणु
		vtotal += var->yres;
		vtotal <<= 1;
	पूर्ण अन्यथा अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE) अणु
		vtotal += var->yres;
		vtotal <<= 2;
	पूर्ण अन्यथा अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
		vtotal += var->yres;
		vtotal <<= 1;
	पूर्ण अन्यथा
		vtotal += var->yres;

	अगर(!(htotal) || !(vtotal)) अणु
		SISFAIL("sisfb: no valid timing data");
	पूर्ण

	search_idx = 0;
	जबतक( (sisbios_mode[search_idx].mode_no[0] != 0) &&
	       (sisbios_mode[search_idx].xres <= var->xres) ) अणु
		अगर( (sisbios_mode[search_idx].xres == var->xres) &&
		    (sisbios_mode[search_idx].yres == var->yres) &&
		    (sisbios_mode[search_idx].bpp == var->bits_per_pixel)) अणु
			अगर((tidx = sisfb_validate_mode(ivideo, search_idx,
						ivideo->currentvbflags)) > 0) अणु
				found_mode = 1;
				search_idx = tidx;
				अवरोध;
			पूर्ण
		पूर्ण
		search_idx++;
	पूर्ण

	अगर(!found_mode) अणु
		search_idx = 0;
		जबतक(sisbios_mode[search_idx].mode_no[0] != 0) अणु
		   अगर( (var->xres <= sisbios_mode[search_idx].xres) &&
		       (var->yres <= sisbios_mode[search_idx].yres) &&
		       (var->bits_per_pixel == sisbios_mode[search_idx].bpp) ) अणु
			अगर((tidx = sisfb_validate_mode(ivideo,search_idx,
						ivideo->currentvbflags)) > 0) अणु
				found_mode = 1;
				search_idx = tidx;
				अवरोध;
			पूर्ण
		   पूर्ण
		   search_idx++;
		पूर्ण
		अगर(found_mode) अणु
			prपूर्णांकk(KERN_DEBUG
				"sisfb: Adapted from %dx%dx%d to %dx%dx%d\n",
				var->xres, var->yres, var->bits_per_pixel,
				sisbios_mode[search_idx].xres,
				sisbios_mode[search_idx].yres,
				var->bits_per_pixel);
			var->xres = sisbios_mode[search_idx].xres;
			var->yres = sisbios_mode[search_idx].yres;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR
				"sisfb: Failed to find supported mode near %dx%dx%d\n",
				var->xres, var->yres, var->bits_per_pixel);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर( ((ivideo->vbflags2 & VB2_LVDS) ||
	     ((ivideo->vbflags2 & VB2_30xBDH) && (ivideo->currentvbflags & CRT2_LCD))) &&
	    (var->bits_per_pixel == 8) ) अणु
		/* Slave modes on LVDS and 301B-DH */
		refresh_rate = 60;
		recalc_घड़ी = true;
	पूर्ण अन्यथा अगर( (ivideo->current_htotal == htotal) &&
		   (ivideo->current_vtotal == vtotal) &&
		   (ivideo->current_pixघड़ी == pixघड़ी) ) अणु
		/* x=x & y=y & c=c -> assume depth change */
		drate = 1000000000 / pixघड़ी;
		hrate = (drate * 1000) / htotal;
		refresh_rate = (अचिन्हित पूर्णांक) (hrate * 2 / vtotal);
	पूर्ण अन्यथा अगर( ( (ivideo->current_htotal != htotal) ||
		     (ivideo->current_vtotal != vtotal) ) &&
		   (ivideo->current_pixघड़ी == var->pixघड़ी) ) अणु
		/* x!=x | y!=y & c=c -> invalid pixघड़ी */
		अगर(ivideo->sisfb_lastrates[sisbios_mode[search_idx].mode_no[ivideo->mni]]) अणु
			refresh_rate =
				ivideo->sisfb_lastrates[sisbios_mode[search_idx].mode_no[ivideo->mni]];
		पूर्ण अन्यथा अगर(ivideo->sisfb_parm_rate != -1) अणु
			/* Sic, sisfb_parm_rate - want to know originally desired rate here */
			refresh_rate = ivideo->sisfb_parm_rate;
		पूर्ण अन्यथा अणु
			refresh_rate = 60;
		पूर्ण
		recalc_घड़ी = true;
	पूर्ण अन्यथा अगर((pixघड़ी) && (htotal) && (vtotal)) अणु
		drate = 1000000000 / pixघड़ी;
		hrate = (drate * 1000) / htotal;
		refresh_rate = (अचिन्हित पूर्णांक) (hrate * 2 / vtotal);
	पूर्ण अन्यथा अगर(ivideo->current_refresh_rate) अणु
		refresh_rate = ivideo->current_refresh_rate;
		recalc_घड़ी = true;
	पूर्ण अन्यथा अणु
		refresh_rate = 60;
		recalc_घड़ी = true;
	पूर्ण

	myrateindex = sisfb_search_refresh_rate(ivideo, refresh_rate, search_idx);

	/* Eventually recalculate timing and घड़ी */
	अगर(recalc_घड़ी) अणु
		अगर(!myrateindex) myrateindex = sisbios_mode[search_idx].rate_idx;
		var->pixघड़ी = (u32) (1000000000 / sisfb_mode_rate_to_dघड़ी(&ivideo->SiS_Pr,
						sisbios_mode[search_idx].mode_no[ivideo->mni],
						myrateindex));
		sisfb_mode_rate_to_ddata(&ivideo->SiS_Pr,
					sisbios_mode[search_idx].mode_no[ivideo->mni],
					myrateindex, var);
		अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE) अणु
			var->pixघड़ी <<= 1;
		पूर्ण
	पूर्ण

	अगर(ivideo->sisfb_thismonitor.datavalid) अणु
		अगर(!sisfb_verअगरy_rate(ivideo, &ivideo->sisfb_thismonitor, search_idx,
				myrateindex, refresh_rate)) अणु
			prपूर्णांकk(KERN_INFO
				"sisfb: WARNING: Refresh rate exceeds monitor specs!\n");
		पूर्ण
	पूर्ण

	/* Adapt RGB settings */
	sisfb_bpp_to_var(ivideo, var);

	अगर(var->xres > var->xres_भव)
		var->xres_भव = var->xres;

	अगर(ivideo->sisfb_ypan) अणु
		maxyres = sisfb_calc_maxyres(ivideo, var);
		अगर(ivideo->sisfb_max) अणु
			var->yres_भव = maxyres;
		पूर्ण अन्यथा अणु
			अगर(var->yres_भव > maxyres) अणु
				var->yres_भव = maxyres;
			पूर्ण
		पूर्ण
		अगर(var->yres_भव <= var->yres) अणु
			var->yres_भव = var->yres;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर(var->yres != var->yres_भव) अणु
			var->yres_भव = var->yres;
		पूर्ण
		var->xoffset = 0;
		var->yoffset = 0;
	पूर्ण

	/* Truncate offsets to maximum अगर too high */
	अगर(var->xoffset > var->xres_भव - var->xres) अणु
		var->xoffset = var->xres_भव - var->xres - 1;
	पूर्ण

	अगर(var->yoffset > var->yres_भव - var->yres) अणु
		var->yoffset = var->yres_भव - var->yres - 1;
	पूर्ण

	/* Set everything अन्यथा to 0 */
	var->red.msb_right =
		var->green.msb_right =
		var->blue.msb_right =
		var->transp.offset =
		var->transp.length =
		var->transp.msb_right = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info* info)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;
	पूर्णांक err;

	अगर (var->vmode & FB_VMODE_YWRAP)
		वापस -EINVAL;

	अगर (var->xoffset + info->var.xres > info->var.xres_भव ||
	    var->yoffset + info->var.yres > info->var.yres_भव)
		वापस -EINVAL;

	err = sisfb_pan_var(ivideo, info, var);
	अगर (err < 0)
		वापस err;

	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;

	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;

	वापस sisfb_myblank(ivideo, blank);
पूर्ण

/* ----------- FBDev related routines क्रम all series ---------- */

अटल पूर्णांक	sisfb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा sis_video_info	*ivideo = (काष्ठा sis_video_info *)info->par;
	काष्ठा sis_memreq	sismemreq;
	काष्ठा fb_vblank	sisvbblank;
	u32			gpu32 = 0;
#अगर_अघोषित __user
#घोषणा __user
#पूर्ण_अगर
	u32 __user 		*argp = (u32 __user *)arg;

	चयन(cmd) अणु
	   हाल FBIO_ALLOC:
		अगर(!capable(CAP_SYS_RAWIO))
			वापस -EPERM;

		अगर(copy_from_user(&sismemreq, (व्योम __user *)arg, माप(sismemreq)))
			वापस -EFAULT;

		sis_दो_स्मृति(&sismemreq);

		अगर(copy_to_user((व्योम __user *)arg, &sismemreq, माप(sismemreq))) अणु
			sis_मुक्त((u32)sismemreq.offset);
			वापस -EFAULT;
		पूर्ण
		अवरोध;

	   हाल FBIO_FREE:
		अगर(!capable(CAP_SYS_RAWIO))
			वापस -EPERM;

		अगर(get_user(gpu32, argp))
			वापस -EFAULT;

		sis_मुक्त(gpu32);
		अवरोध;

	   हाल FBIOGET_VBLANK:

		स_रखो(&sisvbblank, 0, माप(काष्ठा fb_vblank));

		sisvbblank.count = 0;
		sisvbblank.flags = sisfb_setupvbblankflags(ivideo, &sisvbblank.vcount, &sisvbblank.hcount);

		अगर(copy_to_user((व्योम __user *)arg, &sisvbblank, माप(sisvbblank)))
			वापस -EFAULT;

		अवरोध;

	   हाल SISFB_GET_INFO_SIZE:
		वापस put_user(माप(काष्ठा sisfb_info), argp);

	   हाल SISFB_GET_INFO_OLD:
		अगर(ivideo->warncount++ < 10)
			prपूर्णांकk(KERN_INFO
				"sisfb: Deprecated ioctl call received - update your application!\n");
		fallthrough;
	   हाल SISFB_GET_INFO:  /* For communication with X driver */
		ivideo->sisfb_infoblock.sisfb_id         = SISFB_ID;
		ivideo->sisfb_infoblock.sisfb_version    = VER_MAJOR;
		ivideo->sisfb_infoblock.sisfb_revision   = VER_MINOR;
		ivideo->sisfb_infoblock.sisfb_patchlevel = VER_LEVEL;
		ivideo->sisfb_infoblock.chip_id = ivideo->chip_id;
		ivideo->sisfb_infoblock.sisfb_pci_venकरोr = ivideo->chip_venकरोr;
		ivideo->sisfb_infoblock.memory = ivideo->video_size / 1024;
		ivideo->sisfb_infoblock.heapstart = ivideo->heapstart / 1024;
		अगर(ivideo->modechanged) अणु
			ivideo->sisfb_infoblock.fbvidmode = ivideo->mode_no;
		पूर्ण अन्यथा अणु
			ivideo->sisfb_infoblock.fbvidmode = ivideo->modeprechange;
		पूर्ण
		ivideo->sisfb_infoblock.sisfb_caps = ivideo->caps;
		ivideo->sisfb_infoblock.sisfb_tqlen = ivideo->cmdQueueSize / 1024;
		ivideo->sisfb_infoblock.sisfb_pcibus = ivideo->pcibus;
		ivideo->sisfb_infoblock.sisfb_pcislot = ivideo->pcislot;
		ivideo->sisfb_infoblock.sisfb_pcअगरunc = ivideo->pcअगरunc;
		ivideo->sisfb_infoblock.sisfb_lcdpdc = ivideo->detectedpdc;
		ivideo->sisfb_infoblock.sisfb_lcdpdca = ivideo->detectedpdca;
		ivideo->sisfb_infoblock.sisfb_lcda = ivideo->detectedlcda;
		ivideo->sisfb_infoblock.sisfb_vbflags = ivideo->vbflags;
		ivideo->sisfb_infoblock.sisfb_currentvbflags = ivideo->currentvbflags;
		ivideo->sisfb_infoblock.sisfb_scalelcd = ivideo->SiS_Pr.UsePanelScaler;
		ivideo->sisfb_infoblock.sisfb_specialtiming = ivideo->SiS_Pr.SiS_CustomT;
		ivideo->sisfb_infoblock.sisfb_haveemi = ivideo->SiS_Pr.HaveEMI ? 1 : 0;
		ivideo->sisfb_infoblock.sisfb_haveemilcd = ivideo->SiS_Pr.HaveEMILCD ? 1 : 0;
		ivideo->sisfb_infoblock.sisfb_emi30 = ivideo->SiS_Pr.EMI_30;
		ivideo->sisfb_infoblock.sisfb_emi31 = ivideo->SiS_Pr.EMI_31;
		ivideo->sisfb_infoblock.sisfb_emi32 = ivideo->SiS_Pr.EMI_32;
		ivideo->sisfb_infoblock.sisfb_emi33 = ivideo->SiS_Pr.EMI_33;
		ivideo->sisfb_infoblock.sisfb_tvxpos = (u16)(ivideo->tvxpos + 32);
		ivideo->sisfb_infoblock.sisfb_tvypos = (u16)(ivideo->tvypos + 32);
		ivideo->sisfb_infoblock.sisfb_heapsize = ivideo->sisfb_heap_size / 1024;
		ivideo->sisfb_infoblock.sisfb_videooffset = ivideo->video_offset;
		ivideo->sisfb_infoblock.sisfb_curfstn = ivideo->curFSTN;
		ivideo->sisfb_infoblock.sisfb_curdstn = ivideo->curDSTN;
		ivideo->sisfb_infoblock.sisfb_vbflags2 = ivideo->vbflags2;
		ivideo->sisfb_infoblock.sisfb_can_post = ivideo->sisfb_can_post ? 1 : 0;
		ivideo->sisfb_infoblock.sisfb_card_posted = ivideo->sisfb_card_posted ? 1 : 0;
		ivideo->sisfb_infoblock.sisfb_was_boot_device = ivideo->sisfb_was_boot_device ? 1 : 0;

		अगर(copy_to_user((व्योम __user *)arg, &ivideo->sisfb_infoblock,
						माप(ivideo->sisfb_infoblock)))
			वापस -EFAULT;

	        अवरोध;

	   हाल SISFB_GET_VBRSTATUS_OLD:
		अगर(ivideo->warncount++ < 10)
			prपूर्णांकk(KERN_INFO
				"sisfb: Deprecated ioctl call received - update your application!\n");
		fallthrough;
	   हाल SISFB_GET_VBRSTATUS:
		अगर(sisfb_CheckVBRetrace(ivideo))
			वापस put_user((u32)1, argp);
		अन्यथा
			वापस put_user((u32)0, argp);

	   हाल SISFB_GET_AUTOMAXIMIZE_OLD:
		अगर(ivideo->warncount++ < 10)
			prपूर्णांकk(KERN_INFO
				"sisfb: Deprecated ioctl call received - update your application!\n");
		fallthrough;
	   हाल SISFB_GET_AUTOMAXIMIZE:
		अगर(ivideo->sisfb_max)
			वापस put_user((u32)1, argp);
		अन्यथा
			वापस put_user((u32)0, argp);

	   हाल SISFB_SET_AUTOMAXIMIZE_OLD:
		अगर(ivideo->warncount++ < 10)
			prपूर्णांकk(KERN_INFO
				"sisfb: Deprecated ioctl call received - update your application!\n");
		fallthrough;
	   हाल SISFB_SET_AUTOMAXIMIZE:
		अगर(get_user(gpu32, argp))
			वापस -EFAULT;

		ivideo->sisfb_max = (gpu32) ? 1 : 0;
		अवरोध;

	   हाल SISFB_SET_TVPOSOFFSET:
		अगर(get_user(gpu32, argp))
			वापस -EFAULT;

		sisfb_set_TVxposoffset(ivideo, ((पूर्णांक)(gpu32 >> 16)) - 32);
		sisfb_set_TVyposoffset(ivideo, ((पूर्णांक)(gpu32 & 0xffff)) - 32);
		अवरोध;

	   हाल SISFB_GET_TVPOSOFFSET:
		वापस put_user((u32)(((ivideo->tvxpos+32)<<16)|((ivideo->tvypos+32)&0xffff)),
							argp);

	   हाल SISFB_COMMAND:
		अगर(copy_from_user(&ivideo->sisfb_command, (व्योम __user *)arg,
							माप(काष्ठा sisfb_cmd)))
			वापस -EFAULT;

		sisfb_handle_command(ivideo, &ivideo->sisfb_command);

		अगर(copy_to_user((व्योम __user *)arg, &ivideo->sisfb_command,
							माप(काष्ठा sisfb_cmd)))
			वापस -EFAULT;

		अवरोध;

	   हाल SISFB_SET_LOCK:
		अगर(get_user(gpu32, argp))
			वापस -EFAULT;

		ivideo->sisfblocked = (gpu32) ? 1 : 0;
		अवरोध;

	   शेष:
#अगर_घोषित SIS_NEW_CONFIG_COMPAT
		वापस -ENOIOCTLCMD;
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
sisfb_get_fix(काष्ठा fb_fix_screeninfo *fix, पूर्णांक con, काष्ठा fb_info *info)
अणु
	काष्ठा sis_video_info *ivideo = (काष्ठा sis_video_info *)info->par;

	स_रखो(fix, 0, माप(काष्ठा fb_fix_screeninfo));

	strlcpy(fix->id, ivideo->myid, माप(fix->id));

	mutex_lock(&info->mm_lock);
	fix->smem_start  = ivideo->video_base + ivideo->video_offset;
	fix->smem_len    = ivideo->sisfb_mem;
	mutex_unlock(&info->mm_lock);
	fix->type        = FB_TYPE_PACKED_PIXELS;
	fix->type_aux    = 0;
	fix->visual      = (ivideo->video_bpp == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	fix->xpanstep    = 1;
	fix->ypanstep 	 = (ivideo->sisfb_ypan) ? 1 : 0;
	fix->ywrapstep   = 0;
	fix->line_length = ivideo->video_linelength;
	fix->mmio_start  = ivideo->mmio_base;
	fix->mmio_len    = ivideo->mmio_size;
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		fix->accel = FB_ACCEL_SIS_GLAMOUR;
	पूर्ण अन्यथा अगर((ivideo->chip == SIS_330) ||
		  (ivideo->chip == SIS_760) ||
		  (ivideo->chip == SIS_761)) अणु
		fix->accel = FB_ACCEL_SIS_XABRE;
	पूर्ण अन्यथा अगर(ivideo->chip == XGI_20) अणु
		fix->accel = FB_ACCEL_XGI_VOLARI_Z;
	पूर्ण अन्यथा अगर(ivideo->chip >= XGI_40) अणु
		fix->accel = FB_ACCEL_XGI_VOLARI_V;
	पूर्ण अन्यथा अणु
		fix->accel = FB_ACCEL_SIS_GLAMOUR_2;
	पूर्ण

	वापस 0;
पूर्ण

/* ----------------  fb_ops काष्ठाures ----------------- */

अटल स्थिर काष्ठा fb_ops sisfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= sisfb_खोलो,
	.fb_release	= sisfb_release,
	.fb_check_var	= sisfb_check_var,
	.fb_set_par	= sisfb_set_par,
	.fb_setcolreg	= sisfb_setcolreg,
	.fb_pan_display	= sisfb_pan_display,
	.fb_blank	= sisfb_blank,
	.fb_fillrect	= fbcon_sis_fillrect,
	.fb_copyarea	= fbcon_sis_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_sync	= fbcon_sis_sync,
#अगर_घोषित SIS_NEW_CONFIG_COMPAT
	.fb_compat_ioctl= sisfb_ioctl,
#पूर्ण_अगर
	.fb_ioctl	= sisfb_ioctl
पूर्ण;

/* ---------------- Chip generation dependent routines ---------------- */

अटल काष्ठा pci_dev *sisfb_get_northbridge(पूर्णांक basechipid)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक nbridgक्रमागत, nbridgeidx, i;
	अटल स्थिर अचिन्हित लघु nbridgeids[] = अणु
		PCI_DEVICE_ID_SI_540,	/* क्रम SiS 540 VGA */
		PCI_DEVICE_ID_SI_630,	/* क्रम SiS 630/730 VGA */
		PCI_DEVICE_ID_SI_730,
		PCI_DEVICE_ID_SI_550,   /* क्रम SiS 550 VGA */
		PCI_DEVICE_ID_SI_650,   /* क्रम SiS 650/651/740 VGA */
		PCI_DEVICE_ID_SI_651,
		PCI_DEVICE_ID_SI_740,
		PCI_DEVICE_ID_SI_661,	/* क्रम SiS 661/741/660/760/761 VGA */
		PCI_DEVICE_ID_SI_741,
		PCI_DEVICE_ID_SI_660,
		PCI_DEVICE_ID_SI_760,
		PCI_DEVICE_ID_SI_761
	पूर्ण;

	चयन(basechipid) अणु
#अगर_घोषित CONFIG_FB_SIS_300
	हाल SIS_540:	nbridgeidx = 0; nbridgक्रमागत = 1; अवरोध;
	हाल SIS_630:	nbridgeidx = 1; nbridgक्रमागत = 2; अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
	हाल SIS_550:   nbridgeidx = 3; nbridgक्रमागत = 1; अवरोध;
	हाल SIS_650:	nbridgeidx = 4; nbridgक्रमागत = 3; अवरोध;
	हाल SIS_660:	nbridgeidx = 7; nbridgक्रमागत = 5; अवरोध;
#पूर्ण_अगर
	शेष:	वापस शून्य;
	पूर्ण
	क्रम(i = 0; i < nbridgक्रमागत; i++) अणु
		अगर((pdev = pci_get_device(PCI_VENDOR_ID_SI,
				nbridgeids[nbridgeidx+i], शून्य)))
			अवरोध;
	पूर्ण
	वापस pdev;
पूर्ण

अटल पूर्णांक sisfb_get_dram_size(काष्ठा sis_video_info *ivideo)
अणु
#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
	u8 reg;
#पूर्ण_अगर

	ivideo->video_size = 0;
	ivideo->UMAsize = ivideo->LFBsize = 0;

	चयन(ivideo->chip) अणु
#अगर_घोषित CONFIG_FB_SIS_300
	हाल SIS_300:
		reg = SiS_GetReg(SISSR, 0x14);
		ivideo->video_size = ((reg & 0x3F) + 1) << 20;
		अवरोध;
	हाल SIS_540:
	हाल SIS_630:
	हाल SIS_730:
		अगर(!ivideo->nbridge)
			वापस -1;
		pci_पढ़ो_config_byte(ivideo->nbridge, 0x63, &reg);
		ivideo->video_size = 1 << (((reg & 0x70) >> 4) + 21);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
	हाल SIS_315H:
	हाल SIS_315PRO:
	हाल SIS_315:
		reg = SiS_GetReg(SISSR, 0x14);
		ivideo->video_size = (1 << ((reg & 0xf0) >> 4)) << 20;
		चयन((reg >> 2) & 0x03) अणु
		हाल 0x01:
		हाल 0x03:
			ivideo->video_size <<= 1;
			अवरोध;
		हाल 0x02:
			ivideo->video_size += (ivideo->video_size/2);
		पूर्ण
		अवरोध;
	हाल SIS_330:
		reg = SiS_GetReg(SISSR, 0x14);
		ivideo->video_size = (1 << ((reg & 0xf0) >> 4)) << 20;
		अगर(reg & 0x0c) ivideo->video_size <<= 1;
		अवरोध;
	हाल SIS_550:
	हाल SIS_650:
	हाल SIS_740:
		reg = SiS_GetReg(SISSR, 0x14);
		ivideo->video_size = (((reg & 0x3f) + 1) << 2) << 20;
		अवरोध;
	हाल SIS_661:
	हाल SIS_741:
		reg = SiS_GetReg(SISCR, 0x79);
		ivideo->video_size = (1 << ((reg & 0xf0) >> 4)) << 20;
		अवरोध;
	हाल SIS_660:
	हाल SIS_760:
	हाल SIS_761:
		reg = SiS_GetReg(SISCR, 0x79);
		reg = (reg & 0xf0) >> 4;
		अगर(reg)	अणु
			ivideo->video_size = (1 << reg) << 20;
			ivideo->UMAsize = ivideo->video_size;
		पूर्ण
		reg = SiS_GetReg(SISCR, 0x78);
		reg &= 0x30;
		अगर(reg) अणु
			अगर(reg == 0x10) अणु
				ivideo->LFBsize = (32 << 20);
			पूर्ण अन्यथा अणु
				ivideo->LFBsize = (64 << 20);
			पूर्ण
			ivideo->video_size += ivideo->LFBsize;
		पूर्ण
		अवरोध;
	हाल SIS_340:
	हाल XGI_20:
	हाल XGI_40:
		reg = SiS_GetReg(SISSR, 0x14);
		ivideo->video_size = (1 << ((reg & 0xf0) >> 4)) << 20;
		अगर(ivideo->chip != XGI_20) अणु
			reg = (reg & 0x0c) >> 2;
			अगर(ivideo->revision_id == 2) अणु
				अगर(reg & 0x01) reg = 0x02;
				अन्यथा	       reg = 0x00;
			पूर्ण
			अगर(reg == 0x02)		ivideo->video_size <<= 1;
			अन्यथा अगर(reg == 0x03)	ivideo->video_size <<= 2;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* -------------- video bridge device detection --------------- */

अटल व्योम sisfb_detect_VB_connect(काष्ठा sis_video_info *ivideo)
अणु
	u8 cr32, temp;

	/* No CRT2 on XGI Z7 */
	अगर(ivideo->chip == XGI_20) अणु
		ivideo->sisfb_crt1off = 0;
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_FB_SIS_300
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		temp = SiS_GetReg(SISSR, 0x17);
		अगर((temp & 0x0F) && (ivideo->chip != SIS_300)) अणु
			/* PAL/NTSC is stored on SR16 on such machines */
			अगर(!(ivideo->vbflags & (TV_PAL | TV_NTSC | TV_PALM | TV_PALN))) अणु
				temp = SiS_GetReg(SISSR, 0x16);
				अगर(temp & 0x20)
					ivideo->vbflags |= TV_PAL;
				अन्यथा
					ivideo->vbflags |= TV_NTSC;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	cr32 = SiS_GetReg(SISCR, 0x32);

	अगर(cr32 & SIS_CRT1) अणु
		ivideo->sisfb_crt1off = 0;
	पूर्ण अन्यथा अणु
		ivideo->sisfb_crt1off = (cr32 & 0xDF) ? 1 : 0;
	पूर्ण

	ivideo->vbflags &= ~(CRT2_TV | CRT2_LCD | CRT2_VGA);

	अगर(cr32 & SIS_VB_TV)   ivideo->vbflags |= CRT2_TV;
	अगर(cr32 & SIS_VB_LCD)  ivideo->vbflags |= CRT2_LCD;
	अगर(cr32 & SIS_VB_CRT2) ivideo->vbflags |= CRT2_VGA;

	/* Check given parms क्रम hardware compatibility.
	 * (Cannot करो this in the search_xx routines since we करोn't
	 * know what hardware we are running on then)
	 */

	अगर(ivideo->chip != SIS_550) अणु
	   ivideo->sisfb_dstn = ivideo->sisfb_fstn = 0;
	पूर्ण

	अगर(ivideo->sisfb_tvplug != -1) अणु
	   अगर( (ivideo->sisvga_engine != SIS_315_VGA) ||
	       (!(ivideo->vbflags2 & VB2_SISYPBPRBRIDGE)) ) अणु
	      अगर(ivideo->sisfb_tvplug & TV_YPBPR) अणु
		 ivideo->sisfb_tvplug = -1;
		 prपूर्णांकk(KERN_ERR "sisfb: YPbPr not supported\n");
	      पूर्ण
	   पूर्ण
	पूर्ण
	अगर(ivideo->sisfb_tvplug != -1) अणु
	   अगर( (ivideo->sisvga_engine != SIS_315_VGA) ||
	       (!(ivideo->vbflags2 & VB2_SISHIVISIONBRIDGE)) ) अणु
	      अगर(ivideo->sisfb_tvplug & TV_HIVISION) अणु
		 ivideo->sisfb_tvplug = -1;
		 prपूर्णांकk(KERN_ERR "sisfb: HiVision not supported\n");
	      पूर्ण
	   पूर्ण
	पूर्ण
	अगर(ivideo->sisfb_tvstd != -1) अणु
	   अगर( (!(ivideo->vbflags2 & VB2_SISBRIDGE)) &&
	       (!((ivideo->sisvga_engine == SIS_315_VGA) &&
			(ivideo->vbflags2 & VB2_CHRONTEL))) ) अणु
	      अगर(ivideo->sisfb_tvstd & (TV_PALM | TV_PALN | TV_NTSCJ)) अणु
		 ivideo->sisfb_tvstd = -1;
		 prपूर्णांकk(KERN_ERR "sisfb: PALM/PALN/NTSCJ not supported\n");
	      पूर्ण
	   पूर्ण
	पूर्ण

	/* Detect/set TV plug & type */
	अगर(ivideo->sisfb_tvplug != -1) अणु
		ivideo->vbflags |= ivideo->sisfb_tvplug;
	पूर्ण अन्यथा अणु
		अगर(cr32 & SIS_VB_YPBPR)     	 ivideo->vbflags |= (TV_YPBPR|TV_YPBPR525I); /* शेष: 480i */
		अन्यथा अगर(cr32 & SIS_VB_HIVISION)  ivideo->vbflags |= TV_HIVISION;
		अन्यथा अगर(cr32 & SIS_VB_SCART)     ivideo->vbflags |= TV_SCART;
		अन्यथा अणु
			अगर(cr32 & SIS_VB_SVIDEO)    ivideo->vbflags |= TV_SVIDEO;
			अगर(cr32 & SIS_VB_COMPOSITE) ivideo->vbflags |= TV_AVIDEO;
		पूर्ण
	पूर्ण

	अगर(!(ivideo->vbflags & (TV_YPBPR | TV_HIVISION))) अणु
	    अगर(ivideo->sisfb_tvstd != -1) अणु
	       ivideo->vbflags &= ~(TV_NTSC | TV_PAL | TV_PALM | TV_PALN | TV_NTSCJ);
	       ivideo->vbflags |= ivideo->sisfb_tvstd;
	    पूर्ण
	    अगर(ivideo->vbflags & TV_SCART) अणु
	       ivideo->vbflags &= ~(TV_NTSC | TV_PALM | TV_PALN | TV_NTSCJ);
	       ivideo->vbflags |= TV_PAL;
	    पूर्ण
	    अगर(!(ivideo->vbflags & (TV_PAL | TV_NTSC | TV_PALM | TV_PALN | TV_NTSCJ))) अणु
		अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
			temp = SiS_GetReg(SISSR, 0x38);
			अगर(temp & 0x01) ivideo->vbflags |= TV_PAL;
			अन्यथा		ivideo->vbflags |= TV_NTSC;
		पूर्ण अन्यथा अगर((ivideo->chip <= SIS_315PRO) || (ivideo->chip >= SIS_330)) अणु
			temp = SiS_GetReg(SISSR, 0x38);
			अगर(temp & 0x01) ivideo->vbflags |= TV_PAL;
			अन्यथा		ivideo->vbflags |= TV_NTSC;
		पूर्ण अन्यथा अणु
			temp = SiS_GetReg(SISCR, 0x79);
			अगर(temp & 0x20)	ivideo->vbflags |= TV_PAL;
			अन्यथा		ivideo->vbflags |= TV_NTSC;
		पूर्ण
	    पूर्ण
	पूर्ण

	/* Copy क्रमceCRT1 option to CRT1off अगर option is given */
	अगर(ivideo->sisfb_क्रमcecrt1 != -1) अणु
	   ivideo->sisfb_crt1off = (ivideo->sisfb_क्रमcecrt1) ? 0 : 1;
	पूर्ण
पूर्ण

/* ------------------ Sensing routines ------------------ */

अटल bool sisfb_test_DDC1(काष्ठा sis_video_info *ivideo)
अणु
    अचिन्हित लघु old;
    पूर्णांक count = 48;

    old = SiS_ReadDDC1Bit(&ivideo->SiS_Pr);
    करो अणु
	अगर(old != SiS_ReadDDC1Bit(&ivideo->SiS_Pr)) अवरोध;
    पूर्ण जबतक(count--);
    वापस (count != -1);
पूर्ण

अटल व्योम sisfb_sense_crt1(काष्ठा sis_video_info *ivideo)
अणु
    bool mustरुको = false;
    u8  sr1F, cr17;
#अगर_घोषित CONFIG_FB_SIS_315
    u8  cr63=0;
#पूर्ण_अगर
    u16 temp = 0xffff;
    पूर्णांक i;

    sr1F = SiS_GetReg(SISSR, 0x1F);
    SiS_SetRegOR(SISSR, 0x1F, 0x04);
    SiS_SetRegAND(SISSR, 0x1F, 0x3F);
    अगर(sr1F & 0xc0) mustरुको = true;

#अगर_घोषित CONFIG_FB_SIS_315
    अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
       cr63 = SiS_GetReg(SISCR, ivideo->SiS_Pr.SiS_MyCR63);
       cr63 &= 0x40;
       SiS_SetRegAND(SISCR, ivideo->SiS_Pr.SiS_MyCR63, 0xBF);
    पूर्ण
#पूर्ण_अगर

    cr17 = SiS_GetReg(SISCR, 0x17);
    cr17 &= 0x80;
    अगर(!cr17) अणु
       SiS_SetRegOR(SISCR, 0x17, 0x80);
       mustरुको = true;
       SiS_SetReg(SISSR, 0x00, 0x01);
       SiS_SetReg(SISSR, 0x00, 0x03);
    पूर्ण

    अगर(mustरुको) अणु
       क्रम(i=0; i < 10; i++) sisfbरुकोretracecrt1(ivideo);
    पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
    अगर(ivideo->chip >= SIS_330) अणु
       SiS_SetRegAND(SISCR, 0x32, ~0x20);
       अगर(ivideo->chip >= SIS_340) अणु
	   SiS_SetReg(SISCR, 0x57, 0x4a);
       पूर्ण अन्यथा अणु
	   SiS_SetReg(SISCR, 0x57, 0x5f);
       पूर्ण
	SiS_SetRegOR(SISCR, 0x53, 0x02);
	जबतक ((SiS_GetRegByte(SISINPSTAT)) & 0x01)    अवरोध;
	जबतक (!((SiS_GetRegByte(SISINPSTAT)) & 0x01)) अवरोध;
	अगर ((SiS_GetRegByte(SISMISCW)) & 0x10) temp = 1;
	SiS_SetRegAND(SISCR, 0x53, 0xfd);
	SiS_SetRegAND(SISCR, 0x57, 0x00);
    पूर्ण
#पूर्ण_अगर

    अगर(temp == 0xffff) अणु
       i = 3;
       करो अणु
	  temp = SiS_HandleDDC(&ivideo->SiS_Pr, ivideo->vbflags,
		ivideo->sisvga_engine, 0, 0, शून्य, ivideo->vbflags2);
       पूर्ण जबतक(((temp == 0) || (temp == 0xffff)) && i--);

       अगर((temp == 0) || (temp == 0xffff)) अणु
          अगर(sisfb_test_DDC1(ivideo)) temp = 1;
       पूर्ण
    पूर्ण

    अगर((temp) && (temp != 0xffff)) अणु
       SiS_SetRegOR(SISCR, 0x32, 0x20);
    पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
    अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
	SiS_SetRegANDOR(SISCR, ivideo->SiS_Pr.SiS_MyCR63, 0xBF, cr63);
    पूर्ण
#पूर्ण_अगर

    SiS_SetRegANDOR(SISCR, 0x17, 0x7F, cr17);

    SiS_SetReg(SISSR, 0x1F, sr1F);
पूर्ण

/* Determine and detect attached devices on SiS30x */
अटल व्योम SiS_SenseLCD(काष्ठा sis_video_info *ivideo)
अणु
	अचिन्हित अक्षर buffer[256];
	अचिन्हित लघु temp, realcrtno, i;
	u8 reg, cr37 = 0, paneltype = 0;
	u16 xres, yres;

	ivideo->SiS_Pr.PanelSelfDetected = false;

	/* LCD detection only क्रम TMDS bridges */
	अगर(!(ivideo->vbflags2 & VB2_SISTMDSBRIDGE))
		वापस;
	अगर(ivideo->vbflags2 & VB2_30xBDH)
		वापस;

	/* If LCD alपढ़ोy set up by BIOS, skip it */
	reg = SiS_GetReg(SISCR, 0x32);
	अगर(reg & 0x08)
		वापस;

	realcrtno = 1;
	अगर(ivideo->SiS_Pr.DDCPortMixup)
		realcrtno = 0;

	/* Check DDC capabilities */
	temp = SiS_HandleDDC(&ivideo->SiS_Pr, ivideo->vbflags, ivideo->sisvga_engine,
				realcrtno, 0, &buffer[0], ivideo->vbflags2);

	अगर((!temp) || (temp == 0xffff) || (!(temp & 0x02)))
		वापस;

	/* Read DDC data */
	i = 3;  /* Number of retrys */
	करो अणु
		temp = SiS_HandleDDC(&ivideo->SiS_Pr, ivideo->vbflags,
				ivideo->sisvga_engine, realcrtno, 1,
				&buffer[0], ivideo->vbflags2);
	पूर्ण जबतक((temp) && i--);

	अगर(temp)
		वापस;

	/* No digital device */
	अगर(!(buffer[0x14] & 0x80))
		वापस;

	/* First detailed timing preferred timing? */
	अगर(!(buffer[0x18] & 0x02))
		वापस;

	xres = buffer[0x38] | ((buffer[0x3a] & 0xf0) << 4);
	yres = buffer[0x3b] | ((buffer[0x3d] & 0xf0) << 4);

	चयन(xres) अणु
		हाल 1024:
			अगर(yres == 768)
				paneltype = 0x02;
			अवरोध;
		हाल 1280:
			अगर(yres == 1024)
				paneltype = 0x03;
			अवरोध;
		हाल 1600:
			अगर((yres == 1200) && (ivideo->vbflags2 & VB2_30xC))
				paneltype = 0x0b;
			अवरोध;
	पूर्ण

	अगर(!paneltype)
		वापस;

	अगर(buffer[0x23])
		cr37 |= 0x10;

	अगर((buffer[0x47] & 0x18) == 0x18)
		cr37 |= ((((buffer[0x47] & 0x06) ^ 0x06) << 5) | 0x20);
	अन्यथा
		cr37 |= 0xc0;

	SiS_SetReg(SISCR, 0x36, paneltype);
	cr37 &= 0xf1;
	SiS_SetRegANDOR(SISCR, 0x37, 0x0c, cr37);
	SiS_SetRegOR(SISCR, 0x32, 0x08);

	ivideo->SiS_Pr.PanelSelfDetected = true;
पूर्ण

अटल पूर्णांक SISDoSense(काष्ठा sis_video_info *ivideo, u16 type, u16 test)
अणु
    पूर्णांक temp, mytest, result, i, j;

    क्रम(j = 0; j < 10; j++) अणु
       result = 0;
       क्रम(i = 0; i < 3; i++) अणु
          mytest = test;
	   SiS_SetReg(SISPART4, 0x11, (type & 0x00ff));
          temp = (type >> 8) | (mytest & 0x00ff);
	  SiS_SetRegANDOR(SISPART4, 0x10, 0xe0, temp);
          SiS_DDC2Delay(&ivideo->SiS_Pr, 0x1500);
          mytest >>= 8;
          mytest &= 0x7f;
	   temp = SiS_GetReg(SISPART4, 0x03);
          temp ^= 0x0e;
          temp &= mytest;
          अगर(temp == mytest) result++;
#अगर 1
	  SiS_SetReg(SISPART4, 0x11, 0x00);
	  SiS_SetRegAND(SISPART4, 0x10, 0xe0);
	  SiS_DDC2Delay(&ivideo->SiS_Pr, 0x1000);
#पूर्ण_अगर
       पूर्ण
       अगर((result == 0) || (result >= 2)) अवरोध;
    पूर्ण
    वापस result;
पूर्ण

अटल व्योम SiS_Sense30x(काष्ठा sis_video_info *ivideo)
अणु
    u8  backupP4_0d,backupP2_00,backupP2_4d,backupSR_1e,biosflag=0;
    u16 svhs=0, svhs_c=0;
    u16 cvbs=0, cvbs_c=0;
    u16 vga2=0, vga2_c=0;
    पूर्णांक myflag, result;
    अक्षर stdstr[] = "sisfb: Detected";
    अक्षर tvstr[]  = "TV connected to";

    अगर(ivideo->vbflags2 & VB2_301) अणु
       svhs = 0x00b9; cvbs = 0x00b3; vga2 = 0x00d1;
       myflag = SiS_GetReg(SISPART4, 0x01);
       अगर(myflag & 0x04) अणु
	  svhs = 0x00dd; cvbs = 0x00ee; vga2 = 0x00fd;
       पूर्ण
    पूर्ण अन्यथा अगर(ivideo->vbflags2 & (VB2_301B | VB2_302B)) अणु
       svhs = 0x016b; cvbs = 0x0174; vga2 = 0x0190;
    पूर्ण अन्यथा अगर(ivideo->vbflags2 & (VB2_301LV | VB2_302LV)) अणु
       svhs = 0x0200; cvbs = 0x0100;
    पूर्ण अन्यथा अगर(ivideo->vbflags2 & (VB2_301C | VB2_302ELV | VB2_307T | VB2_307LV)) अणु
       svhs = 0x016b; cvbs = 0x0110; vga2 = 0x0190;
    पूर्ण अन्यथा
       वापस;

    vga2_c = 0x0e08; svhs_c = 0x0404; cvbs_c = 0x0804;
    अगर(ivideo->vbflags & (VB2_301LV|VB2_302LV|VB2_302ELV|VB2_307LV)) अणु
       svhs_c = 0x0408; cvbs_c = 0x0808;
    पूर्ण

    biosflag = 2;
    अगर(ivideo->haveXGIROM) अणु
       biosflag = ivideo->bios_abase[0x58] & 0x03;
    पूर्ण अन्यथा अगर(ivideo->newrom) अणु
       अगर(ivideo->bios_abase[0x5d] & 0x04) biosflag |= 0x01;
    पूर्ण अन्यथा अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
       अगर(ivideo->bios_abase) अणु
          biosflag = ivideo->bios_abase[0xfe] & 0x03;
       पूर्ण
    पूर्ण

    अगर(ivideo->chip == SIS_300) अणु
       myflag = SiS_GetReg(SISSR, 0x3b);
       अगर(!(myflag & 0x01)) vga2 = vga2_c = 0;
    पूर्ण

    अगर(!(ivideo->vbflags2 & VB2_SISVGA2BRIDGE)) अणु
       vga2 = vga2_c = 0;
    पूर्ण

    backupSR_1e = SiS_GetReg(SISSR, 0x1e);
    SiS_SetRegOR(SISSR, 0x1e, 0x20);

    backupP4_0d = SiS_GetReg(SISPART4, 0x0d);
    अगर(ivideo->vbflags2 & VB2_30xC) अणु
	SiS_SetRegANDOR(SISPART4, 0x0d, ~0x07, 0x01);
    पूर्ण अन्यथा अणु
       SiS_SetRegOR(SISPART4, 0x0d, 0x04);
    पूर्ण
    SiS_DDC2Delay(&ivideo->SiS_Pr, 0x2000);

    backupP2_00 = SiS_GetReg(SISPART2, 0x00);
    SiS_SetReg(SISPART2, 0x00, ((backupP2_00 | 0x1c) & 0xfc));

    backupP2_4d = SiS_GetReg(SISPART2, 0x4d);
    अगर(ivideo->vbflags2 & VB2_SISYPBPRBRIDGE) अणु
	SiS_SetReg(SISPART2, 0x4d, (backupP2_4d & ~0x10));
    पूर्ण

    अगर(!(ivideo->vbflags2 & VB2_30xCLV)) अणु
       SISDoSense(ivideo, 0, 0);
    पूर्ण

    SiS_SetRegAND(SISCR, 0x32, ~0x14);

    अगर(vga2_c || vga2) अणु
       अगर(SISDoSense(ivideo, vga2, vga2_c)) अणु
          अगर(biosflag & 0x01) अणु
	     prपूर्णांकk(KERN_INFO "%s %s SCART output\n", stdstr, tvstr);
	     SiS_SetRegOR(SISCR, 0x32, 0x04);
	  पूर्ण अन्यथा अणु
	     prपूर्णांकk(KERN_INFO "%s secondary VGA connection\n", stdstr);
	     SiS_SetRegOR(SISCR, 0x32, 0x10);
	  पूर्ण
       पूर्ण
    पूर्ण

    SiS_SetRegAND(SISCR, 0x32, 0x3f);

    अगर(ivideo->vbflags2 & VB2_30xCLV) अणु
       SiS_SetRegOR(SISPART4, 0x0d, 0x04);
    पूर्ण

    अगर((ivideo->sisvga_engine == SIS_315_VGA) && (ivideo->vbflags2 & VB2_SISYPBPRBRIDGE)) अणु
       SiS_SetReg(SISPART2, 0x4d, (backupP2_4d | 0x10));
       SiS_DDC2Delay(&ivideo->SiS_Pr, 0x2000);
       अगर((result = SISDoSense(ivideo, svhs, 0x0604))) अणु
          अगर((result = SISDoSense(ivideo, cvbs, 0x0804))) अणु
	     prपूर्णांकk(KERN_INFO "%s %s YPbPr component output\n", stdstr, tvstr);
	     SiS_SetRegOR(SISCR, 0x32, 0x80);
	  पूर्ण
       पूर्ण
       SiS_SetReg(SISPART2, 0x4d, backupP2_4d);
    पूर्ण

    SiS_SetRegAND(SISCR, 0x32, ~0x03);

    अगर(!(ivideo->vbflags & TV_YPBPR)) अणु
       अगर((result = SISDoSense(ivideo, svhs, svhs_c))) अणु
          prपूर्णांकk(KERN_INFO "%s %s SVIDEO output\n", stdstr, tvstr);
	   SiS_SetRegOR(SISCR, 0x32, 0x02);
       पूर्ण
       अगर((biosflag & 0x02) || (!result)) अणु
          अगर(SISDoSense(ivideo, cvbs, cvbs_c)) अणु
	     prपूर्णांकk(KERN_INFO "%s %s COMPOSITE output\n", stdstr, tvstr);
	     SiS_SetRegOR(SISCR, 0x32, 0x01);
          पूर्ण
       पूर्ण
    पूर्ण

    SISDoSense(ivideo, 0, 0);

    SiS_SetReg(SISPART2, 0x00, backupP2_00);
    SiS_SetReg(SISPART4, 0x0d, backupP4_0d);
    SiS_SetReg(SISSR, 0x1e, backupSR_1e);

    अगर(ivideo->vbflags2 & VB2_30xCLV) अणु
	biosflag = SiS_GetReg(SISPART2, 0x00);
       अगर(biosflag & 0x20) अणु
          क्रम(myflag = 2; myflag > 0; myflag--) अणु
	     biosflag ^= 0x20;
	     SiS_SetReg(SISPART2, 0x00, biosflag);
	  पूर्ण
       पूर्ण
    पूर्ण

    SiS_SetReg(SISPART2, 0x00, backupP2_00);
पूर्ण

/* Determine and detect attached TV's on Chrontel */
अटल व्योम SiS_SenseCh(काष्ठा sis_video_info *ivideo)
अणु
#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
    u8 temp1, temp2;
    अक्षर stdstr[] = "sisfb: Chrontel: Detected TV connected to";
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_300
    अचिन्हित अक्षर test[3];
    पूर्णांक i;
#पूर्ण_अगर

    अगर(ivideo->chip < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300
       ivideo->SiS_Pr.SiS_IF_DEF_CH70xx = 1;		/* Chrontel 700x */
       SiS_SetChrontelGPIO(&ivideo->SiS_Pr, 0x9c);	/* Set general purpose IO क्रम Chrontel communication */
       SiS_DDC2Delay(&ivideo->SiS_Pr, 1000);
       temp1 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x25);
       /* See Chrontel TB31 क्रम explanation */
       temp2 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x0e);
       अगर(((temp2 & 0x07) == 0x01) || (temp2 & 0x04)) अणु
	  SiS_SetCH700x(&ivideo->SiS_Pr, 0x0e, 0x0b);
	  SiS_DDC2Delay(&ivideo->SiS_Pr, 300);
       पूर्ण
       temp2 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x25);
       अगर(temp2 != temp1) temp1 = temp2;

       अगर((temp1 >= 0x22) && (temp1 <= 0x50)) अणु
	   /* Read घातer status */
	   temp1 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x0e);
	   अगर((temp1 & 0x03) != 0x03) अणु
		/* Power all outमाला_दो */
		SiS_SetCH700x(&ivideo->SiS_Pr, 0x0e,0x0b);
		SiS_DDC2Delay(&ivideo->SiS_Pr, 300);
	   पूर्ण
	   /* Sense connected TV devices */
	   क्रम(i = 0; i < 3; i++) अणु
	       SiS_SetCH700x(&ivideo->SiS_Pr, 0x10, 0x01);
	       SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	       SiS_SetCH700x(&ivideo->SiS_Pr, 0x10, 0x00);
	       SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	       temp1 = SiS_GetCH700x(&ivideo->SiS_Pr, 0x10);
	       अगर(!(temp1 & 0x08))       test[i] = 0x02;
	       अन्यथा अगर(!(temp1 & 0x02))  test[i] = 0x01;
	       अन्यथा                      test[i] = 0;
	       SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	   पूर्ण

	   अगर(test[0] == test[1])      temp1 = test[0];
	   अन्यथा अगर(test[0] == test[2]) temp1 = test[0];
	   अन्यथा अगर(test[1] == test[2]) temp1 = test[1];
	   अन्यथा अणु
		prपूर्णांकk(KERN_INFO
			"sisfb: TV detection unreliable - test results varied\n");
		temp1 = test[2];
	   पूर्ण
	   अगर(temp1 == 0x02) अणु
		prपूर्णांकk(KERN_INFO "%s SVIDEO output\n", stdstr);
		ivideo->vbflags |= TV_SVIDEO;
		SiS_SetRegOR(SISCR, 0x32, 0x02);
		SiS_SetRegAND(SISCR, 0x32, ~0x05);
	   पूर्ण अन्यथा अगर (temp1 == 0x01) अणु
		prपूर्णांकk(KERN_INFO "%s CVBS output\n", stdstr);
		ivideo->vbflags |= TV_AVIDEO;
		SiS_SetRegOR(SISCR, 0x32, 0x01);
		SiS_SetRegAND(SISCR, 0x32, ~0x06);
	   पूर्ण अन्यथा अणु
		SiS_SetCH70xxANDOR(&ivideo->SiS_Pr, 0x0e, 0x01, 0xF8);
		SiS_SetRegAND(SISCR, 0x32, ~0x07);
	   पूर्ण
       पूर्ण अन्यथा अगर(temp1 == 0) अणु
	  SiS_SetCH70xxANDOR(&ivideo->SiS_Pr, 0x0e, 0x01, 0xF8);
	  SiS_SetRegAND(SISCR, 0x32, ~0x07);
       पूर्ण
       /* Set general purpose IO क्रम Chrontel communication */
       SiS_SetChrontelGPIO(&ivideo->SiS_Pr, 0x00);
#पूर्ण_अगर

    पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315
	ivideo->SiS_Pr.SiS_IF_DEF_CH70xx = 2;		/* Chrontel 7019 */
	temp1 = SiS_GetCH701x(&ivideo->SiS_Pr, 0x49);
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x49, 0x20);
	SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	temp2 = SiS_GetCH701x(&ivideo->SiS_Pr, 0x20);
	temp2 |= 0x01;
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x20, temp2);
	SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	temp2 ^= 0x01;
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x20, temp2);
	SiS_DDC2Delay(&ivideo->SiS_Pr, 0x96);
	temp2 = SiS_GetCH701x(&ivideo->SiS_Pr, 0x20);
	SiS_SetCH701x(&ivideo->SiS_Pr, 0x49, temp1);
	temp1 = 0;
	अगर(temp2 & 0x02) temp1 |= 0x01;
	अगर(temp2 & 0x10) temp1 |= 0x01;
	अगर(temp2 & 0x04) temp1 |= 0x02;
	अगर( (temp1 & 0x01) && (temp1 & 0x02) ) temp1 = 0x04;
	चयन(temp1) अणु
	हाल 0x01:
	     prपूर्णांकk(KERN_INFO "%s CVBS output\n", stdstr);
	     ivideo->vbflags |= TV_AVIDEO;
	     SiS_SetRegOR(SISCR, 0x32, 0x01);
	     SiS_SetRegAND(SISCR, 0x32, ~0x06);
	     अवरोध;
	हाल 0x02:
	     prपूर्णांकk(KERN_INFO "%s SVIDEO output\n", stdstr);
	     ivideo->vbflags |= TV_SVIDEO;
	     SiS_SetRegOR(SISCR, 0x32, 0x02);
	     SiS_SetRegAND(SISCR, 0x32, ~0x05);
	     अवरोध;
	हाल 0x04:
	     prपूर्णांकk(KERN_INFO "%s SCART output\n", stdstr);
	     SiS_SetRegOR(SISCR, 0x32, 0x04);
	     SiS_SetRegAND(SISCR, 0x32, ~0x03);
	     अवरोध;
	शेष:
	     SiS_SetRegAND(SISCR, 0x32, ~0x07);
	पूर्ण
#पूर्ण_अगर
    पूर्ण
पूर्ण

अटल व्योम sisfb_get_VB_type(काष्ठा sis_video_info *ivideo)
अणु
	अक्षर stdstr[]    = "sisfb: Detected";
	अक्षर bridgestr[] = "video bridge";
	u8 vb_chipid;
	u8 reg;

	/* No CRT2 on XGI Z7 */
	अगर(ivideo->chip == XGI_20)
		वापस;

	vb_chipid = SiS_GetReg(SISPART4, 0x00);
	चयन(vb_chipid) अणु
	हाल 0x01:
		reg = SiS_GetReg(SISPART4, 0x01);
		अगर(reg < 0xb0) अणु
			ivideo->vbflags |= VB_301;	/* Deprecated */
			ivideo->vbflags2 |= VB2_301;
			prपूर्णांकk(KERN_INFO "%s SiS301 %s\n", stdstr, bridgestr);
		पूर्ण अन्यथा अगर(reg < 0xc0) अणु
			ivideo->vbflags |= VB_301B;	/* Deprecated */
			ivideo->vbflags2 |= VB2_301B;
			reg = SiS_GetReg(SISPART4, 0x23);
			अगर(!(reg & 0x02)) अणु
			   ivideo->vbflags |= VB_30xBDH;	/* Deprecated */
			   ivideo->vbflags2 |= VB2_30xBDH;
			   prपूर्णांकk(KERN_INFO "%s SiS301B-DH %s\n", stdstr, bridgestr);
			पूर्ण अन्यथा अणु
			   prपूर्णांकk(KERN_INFO "%s SiS301B %s\n", stdstr, bridgestr);
			पूर्ण
		पूर्ण अन्यथा अगर(reg < 0xd0) अणु
			ivideo->vbflags |= VB_301C;	/* Deprecated */
			ivideo->vbflags2 |= VB2_301C;
			prपूर्णांकk(KERN_INFO "%s SiS301C %s\n", stdstr, bridgestr);
		पूर्ण अन्यथा अगर(reg < 0xe0) अणु
			ivideo->vbflags |= VB_301LV;	/* Deprecated */
			ivideo->vbflags2 |= VB2_301LV;
			prपूर्णांकk(KERN_INFO "%s SiS301LV %s\n", stdstr, bridgestr);
		पूर्ण अन्यथा अगर(reg <= 0xe1) अणु
			reg = SiS_GetReg(SISPART4, 0x39);
			अगर(reg == 0xff) अणु
			   ivideo->vbflags |= VB_302LV;	/* Deprecated */
			   ivideo->vbflags2 |= VB2_302LV;
			   prपूर्णांकk(KERN_INFO "%s SiS302LV %s\n", stdstr, bridgestr);
			पूर्ण अन्यथा अणु
			   ivideo->vbflags |= VB_301C;	/* Deprecated */
			   ivideo->vbflags2 |= VB2_301C;
			   prपूर्णांकk(KERN_INFO "%s SiS301C(P4) %s\n", stdstr, bridgestr);
#अगर 0
			   ivideo->vbflags |= VB_302ELV;	/* Deprecated */
			   ivideo->vbflags2 |= VB2_302ELV;
			   prपूर्णांकk(KERN_INFO "%s SiS302ELV %s\n", stdstr, bridgestr);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 0x02:
		ivideo->vbflags |= VB_302B;	/* Deprecated */
		ivideo->vbflags2 |= VB2_302B;
		prपूर्णांकk(KERN_INFO "%s SiS302B %s\n", stdstr, bridgestr);
		अवरोध;
	पूर्ण

	अगर((!(ivideo->vbflags2 & VB2_VIDEOBRIDGE)) && (ivideo->chip != SIS_300)) अणु
		reg = SiS_GetReg(SISCR, 0x37);
		reg &= SIS_EXTERNAL_CHIP_MASK;
		reg >>= 1;
		अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
#अगर_घोषित CONFIG_FB_SIS_300
			चयन(reg) अणु
			   हाल SIS_EXTERNAL_CHIP_LVDS:
				ivideo->vbflags |= VB_LVDS;	/* Deprecated */
				ivideo->vbflags2 |= VB2_LVDS;
				अवरोध;
			   हाल SIS_EXTERNAL_CHIP_TRUMPION:
				ivideo->vbflags |= (VB_LVDS | VB_TRUMPION);	/* Deprecated */
				ivideo->vbflags2 |= (VB2_LVDS | VB2_TRUMPION);
				अवरोध;
			   हाल SIS_EXTERNAL_CHIP_CHRONTEL:
				ivideo->vbflags |= VB_CHRONTEL;	/* Deprecated */
				ivideo->vbflags2 |= VB2_CHRONTEL;
				अवरोध;
			   हाल SIS_EXTERNAL_CHIP_LVDS_CHRONTEL:
				ivideo->vbflags |= (VB_LVDS | VB_CHRONTEL);	/* Deprecated */
				ivideo->vbflags2 |= (VB2_LVDS | VB2_CHRONTEL);
				अवरोध;
			पूर्ण
			अगर(ivideo->vbflags2 & VB2_CHRONTEL) ivideo->chronteltype = 1;
#पूर्ण_अगर
		पूर्ण अन्यथा अगर(ivideo->chip < SIS_661) अणु
#अगर_घोषित CONFIG_FB_SIS_315
			चयन (reg) अणु
			   हाल SIS310_EXTERNAL_CHIP_LVDS:
				ivideo->vbflags |= VB_LVDS;	/* Deprecated */
				ivideo->vbflags2 |= VB2_LVDS;
				अवरोध;
			   हाल SIS310_EXTERNAL_CHIP_LVDS_CHRONTEL:
				ivideo->vbflags |= (VB_LVDS | VB_CHRONTEL);	/* Deprecated */
				ivideo->vbflags2 |= (VB2_LVDS | VB2_CHRONTEL);
				अवरोध;
			पूर्ण
			अगर(ivideo->vbflags2 & VB2_CHRONTEL) ivideo->chronteltype = 2;
#पूर्ण_अगर
		पूर्ण अन्यथा अगर(ivideo->chip >= SIS_661) अणु
#अगर_घोषित CONFIG_FB_SIS_315
			reg = SiS_GetReg(SISCR, 0x38);
			reg >>= 5;
			चयन(reg) अणु
			   हाल 0x02:
				ivideo->vbflags |= VB_LVDS;	/* Deprecated */
				ivideo->vbflags2 |= VB2_LVDS;
				अवरोध;
			   हाल 0x03:
				ivideo->vbflags |= (VB_LVDS | VB_CHRONTEL);	/* Deprecated */
				ivideo->vbflags2 |= (VB2_LVDS | VB2_CHRONTEL);
				अवरोध;
			   हाल 0x04:
				ivideo->vbflags |= (VB_LVDS | VB_CONEXANT);	/* Deprecated */
				ivideo->vbflags2 |= (VB2_LVDS | VB2_CONEXANT);
				अवरोध;
			पूर्ण
			अगर(ivideo->vbflags2 & VB2_CHRONTEL) ivideo->chronteltype = 2;
#पूर्ण_अगर
		पूर्ण
		अगर(ivideo->vbflags2 & VB2_LVDS) अणु
		   prपूर्णांकk(KERN_INFO "%s LVDS transmitter\n", stdstr);
		पूर्ण
		अगर((ivideo->sisvga_engine == SIS_300_VGA) && (ivideo->vbflags2 & VB2_TRUMPION)) अणु
		   prपूर्णांकk(KERN_INFO "%s Trumpion Zurac LCD scaler\n", stdstr);
		पूर्ण
		अगर(ivideo->vbflags2 & VB2_CHRONTEL) अणु
		   prपूर्णांकk(KERN_INFO "%s Chrontel TV encoder\n", stdstr);
		पूर्ण
		अगर((ivideo->chip >= SIS_661) && (ivideo->vbflags2 & VB2_CONEXANT)) अणु
		   prपूर्णांकk(KERN_INFO "%s Conexant external device\n", stdstr);
		पूर्ण
	पूर्ण

	अगर(ivideo->vbflags2 & VB2_SISBRIDGE) अणु
		SiS_SenseLCD(ivideo);
		SiS_Sense30x(ivideo);
	पूर्ण अन्यथा अगर(ivideo->vbflags2 & VB2_CHRONTEL) अणु
		SiS_SenseCh(ivideo);
	पूर्ण
पूर्ण

/* ---------- Engine initialization routines ------------ */

अटल व्योम
sisfb_engine_init(काष्ठा sis_video_info *ivideo)
अणु

	/* Initialize command queue (we use MMIO only) */

	/* BEFORE THIS IS CALLED, THE ENGINES *MUST* BE SYNC'ED */

	ivideo->caps &= ~(TURBO_QUEUE_CAP    |
			  MMIO_CMD_QUEUE_CAP |
			  VM_CMD_QUEUE_CAP   |
			  AGP_CMD_QUEUE_CAP);

#अगर_घोषित CONFIG_FB_SIS_300
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		u32 tqueue_pos;
		u8 tq_state;

		tqueue_pos = (ivideo->video_size - ivideo->cmdQueueSize) / (64 * 1024);

		tq_state = SiS_GetReg(SISSR, IND_SIS_TURBOQUEUE_SET);
		tq_state |= 0xf0;
		tq_state &= 0xfc;
		tq_state |= (u8)(tqueue_pos >> 8);
		SiS_SetReg(SISSR, IND_SIS_TURBOQUEUE_SET, tq_state);

		SiS_SetReg(SISSR, IND_SIS_TURBOQUEUE_ADR, (u8)(tqueue_pos & 0xff));

		ivideo->caps |= TURBO_QUEUE_CAP;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
	अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
		u32 tempq = 0, templ;
		u8  temp;

		अगर(ivideo->chip == XGI_20) अणु
			चयन(ivideo->cmdQueueSize) अणु
			हाल (64 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_Z7_64k;
				अवरोध;
			हाल (128 * 1024):
			शेष:
				temp = SIS_CMD_QUEUE_SIZE_Z7_128k;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन(ivideo->cmdQueueSize) अणु
			हाल (4 * 1024 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_4M;
				अवरोध;
			हाल (2 * 1024 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_2M;
				अवरोध;
			हाल (1 * 1024 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_1M;
				अवरोध;
			शेष:
			हाल (512 * 1024):
				temp = SIS_CMD_QUEUE_SIZE_512k;
			पूर्ण
		पूर्ण

		SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_THRESHOLD, COMMAND_QUEUE_THRESHOLD);
		SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, SIS_CMD_QUEUE_RESET);

		अगर((ivideo->chip >= XGI_40) && ivideo->modechanged) अणु
			/* Must disable dual pipe on XGI_40. Can't करो
			 * this in MMIO mode, because it requires
			 * setting/clearing a bit in the MMIO fire trigger
			 * रेजिस्टर.
			 */
			अगर(!((templ = MMIO_IN32(ivideo->mmio_vbase, 0x8240)) & (1 << 10))) अणु

				MMIO_OUT32(ivideo->mmio_vbase, Q_WRITE_PTR, 0);

				SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, (temp | SIS_VRAM_CMDQUEUE_ENABLE));

				tempq = MMIO_IN32(ivideo->mmio_vbase, Q_READ_PTR);
				MMIO_OUT32(ivideo->mmio_vbase, Q_WRITE_PTR, tempq);

				tempq = (u32)(ivideo->video_size - ivideo->cmdQueueSize);
				MMIO_OUT32(ivideo->mmio_vbase, Q_BASE_ADDR, tempq);

				ग_लिखोl(0x16800000 + 0x8240, ivideo->video_vbase + tempq);
				ग_लिखोl(templ | (1 << 10), ivideo->video_vbase + tempq + 4);
				ग_लिखोl(0x168F0000, ivideo->video_vbase + tempq + 8);
				ग_लिखोl(0x168F0000, ivideo->video_vbase + tempq + 12);

				MMIO_OUT32(ivideo->mmio_vbase, Q_WRITE_PTR, (tempq + 16));

				sisfb_syncaccel(ivideo);

				SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, SIS_CMD_QUEUE_RESET);

			पूर्ण
		पूर्ण

		tempq = MMIO_IN32(ivideo->mmio_vbase, MMIO_QUEUE_READPORT);
		MMIO_OUT32(ivideo->mmio_vbase, MMIO_QUEUE_WRITEPORT, tempq);

		temp |= (SIS_MMIO_CMD_ENABLE | SIS_CMD_AUTO_CORR);
		SiS_SetReg(SISSR, IND_SIS_CMDQUEUE_SET, temp);

		tempq = (u32)(ivideo->video_size - ivideo->cmdQueueSize);
		MMIO_OUT32(ivideo->mmio_vbase, MMIO_QUEUE_PHYBASE, tempq);

		ivideo->caps |= MMIO_CMD_QUEUE_CAP;
	पूर्ण
#पूर्ण_अगर

	ivideo->engineok = 1;
पूर्ण

अटल व्योम sisfb_detect_lcd_type(काष्ठा sis_video_info *ivideo)
अणु
	u8 reg;
	पूर्णांक i;

	reg = SiS_GetReg(SISCR, 0x36);
	reg &= 0x0f;
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		ivideo->CRT2LCDType = sis300paneltype[reg];
	पूर्ण अन्यथा अगर(ivideo->chip >= SIS_661) अणु
		ivideo->CRT2LCDType = sis661paneltype[reg];
	पूर्ण अन्यथा अणु
		ivideo->CRT2LCDType = sis310paneltype[reg];
		अगर((ivideo->chip == SIS_550) && (sisfb_fstn)) अणु
			अगर((ivideo->CRT2LCDType != LCD_320x240_2) &&
			   (ivideo->CRT2LCDType != LCD_320x240_3)) अणु
				ivideo->CRT2LCDType = LCD_320x240;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर(ivideo->CRT2LCDType == LCD_UNKNOWN) अणु
		/* For broken BIOSes: Assume 1024x768, RGB18 */
		ivideo->CRT2LCDType = LCD_1024x768;
		SiS_SetRegANDOR(SISCR, 0x36, 0xf0, 0x02);
		SiS_SetRegANDOR(SISCR, 0x37, 0xee, 0x01);
		prपूर्णांकk(KERN_DEBUG "sisfb: Invalid panel ID (%02x), assuming 1024x768, RGB18\n", reg);
	पूर्ण

	क्रम(i = 0; i < SIS_LCD_NUMBER; i++) अणु
		अगर(ivideo->CRT2LCDType == sis_lcd_data[i].lcdtype) अणु
			ivideo->lcdxres = sis_lcd_data[i].xres;
			ivideo->lcdyres = sis_lcd_data[i].yres;
			ivideo->lcddeभ_शेषeidx = sis_lcd_data[i].शेष_mode_idx;
			अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_FB_SIS_300
	अगर(ivideo->SiS_Pr.SiS_CustomT == CUT_BARCO1366) अणु
		ivideo->lcdxres = 1360; ivideo->lcdyres = 1024;
		ivideo->lcddeभ_शेषeidx = DEFAULT_MODE_1360;
	पूर्ण अन्यथा अगर(ivideo->SiS_Pr.SiS_CustomT == CUT_PANEL848) अणु
		ivideo->lcdxres =  848; ivideo->lcdyres =  480;
		ivideo->lcddeभ_शेषeidx = DEFAULT_MODE_848;
	पूर्ण अन्यथा अगर(ivideo->SiS_Pr.SiS_CustomT == CUT_PANEL856) अणु
		ivideo->lcdxres =  856; ivideo->lcdyres =  480;
		ivideo->lcddeभ_शेषeidx = DEFAULT_MODE_856;
	पूर्ण
#पूर्ण_अगर

	prपूर्णांकk(KERN_DEBUG "sisfb: Detected %dx%d flat panel\n",
			ivideo->lcdxres, ivideo->lcdyres);
पूर्ण

अटल व्योम sisfb_save_pdc_emi(काष्ठा sis_video_info *ivideo)
अणु
#अगर_घोषित CONFIG_FB_SIS_300
	/* Save the current PanelDelayCompensation अगर the LCD is currently used */
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		अगर(ivideo->vbflags2 & (VB2_LVDS | VB2_30xBDH)) अणु
			पूर्णांक पंचांगp;
			पंचांगp = SiS_GetReg(SISCR, 0x30);
			अगर(पंचांगp & 0x20) अणु
				/* Currently on LCD? If yes, पढ़ो current pdc */
				ivideo->detectedpdc = SiS_GetReg(SISPART1, 0x13);
				ivideo->detectedpdc &= 0x3c;
				अगर(ivideo->SiS_Pr.PDC == -1) अणु
					/* Let option override detection */
					ivideo->SiS_Pr.PDC = ivideo->detectedpdc;
				पूर्ण
				prपूर्णांकk(KERN_INFO "sisfb: Detected LCD PDC 0x%02x\n",
					ivideo->detectedpdc);
			पूर्ण
			अगर((ivideo->SiS_Pr.PDC != -1) &&
			   (ivideo->SiS_Pr.PDC != ivideo->detectedpdc)) अणु
				prपूर्णांकk(KERN_INFO "sisfb: Using LCD PDC 0x%02x\n",
					ivideo->SiS_Pr.PDC);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
	अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु

		/* Try to find about LCDA */
		अगर(ivideo->vbflags2 & VB2_SISLCDABRIDGE) अणु
			पूर्णांक पंचांगp;
			पंचांगp = SiS_GetReg(SISPART1, 0x13);
			अगर(पंचांगp & 0x04) अणु
				ivideo->SiS_Pr.SiS_UseLCDA = true;
				ivideo->detectedlcda = 0x03;
			पूर्ण
		पूर्ण

		/* Save PDC */
		अगर(ivideo->vbflags2 & VB2_SISLVDSBRIDGE) अणु
			पूर्णांक पंचांगp;
			पंचांगp = SiS_GetReg(SISCR, 0x30);
			अगर((पंचांगp & 0x20) || (ivideo->detectedlcda != 0xff)) अणु
				/* Currently on LCD? If yes, पढ़ो current pdc */
				u8 pdc;
				pdc = SiS_GetReg(SISPART1, 0x2D);
				ivideo->detectedpdc  = (pdc & 0x0f) << 1;
				ivideo->detectedpdca = (pdc & 0xf0) >> 3;
				pdc = SiS_GetReg(SISPART1, 0x35);
				ivideo->detectedpdc |= ((pdc >> 7) & 0x01);
				pdc = SiS_GetReg(SISPART1, 0x20);
				ivideo->detectedpdca |= ((pdc >> 6) & 0x01);
				अगर(ivideo->newrom) अणु
					/* New ROM invalidates other PDC resp. */
					अगर(ivideo->detectedlcda != 0xff) अणु
						ivideo->detectedpdc = 0xff;
					पूर्ण अन्यथा अणु
						ivideo->detectedpdca = 0xff;
					पूर्ण
				पूर्ण
				अगर(ivideo->SiS_Pr.PDC == -1) अणु
					अगर(ivideo->detectedpdc != 0xff) अणु
						ivideo->SiS_Pr.PDC = ivideo->detectedpdc;
					पूर्ण
				पूर्ण
				अगर(ivideo->SiS_Pr.PDCA == -1) अणु
					अगर(ivideo->detectedpdca != 0xff) अणु
						ivideo->SiS_Pr.PDCA = ivideo->detectedpdca;
					पूर्ण
				पूर्ण
				अगर(ivideo->detectedpdc != 0xff) अणु
					prपूर्णांकk(KERN_INFO
						"sisfb: Detected LCD PDC 0x%02x (for LCD=CRT2)\n",
						ivideo->detectedpdc);
				पूर्ण
				अगर(ivideo->detectedpdca != 0xff) अणु
					prपूर्णांकk(KERN_INFO
						"sisfb: Detected LCD PDC1 0x%02x (for LCD=CRT1)\n",
						ivideo->detectedpdca);
				पूर्ण
			पूर्ण

			/* Save EMI */
			अगर(ivideo->vbflags2 & VB2_SISEMIBRIDGE) अणु
				ivideo->SiS_Pr.EMI_30 = SiS_GetReg(SISPART4, 0x30);
				ivideo->SiS_Pr.EMI_31 = SiS_GetReg(SISPART4, 0x31);
				ivideo->SiS_Pr.EMI_32 = SiS_GetReg(SISPART4, 0x32);
				ivideo->SiS_Pr.EMI_33 = SiS_GetReg(SISPART4, 0x33);
				ivideo->SiS_Pr.HaveEMI = true;
				अगर((पंचांगp & 0x20) || (ivideo->detectedlcda != 0xff)) अणु
					ivideo->SiS_Pr.HaveEMILCD = true;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Let user override detected PDCs (all bridges) */
		अगर(ivideo->vbflags2 & VB2_30xBLV) अणु
			अगर((ivideo->SiS_Pr.PDC != -1) &&
			   (ivideo->SiS_Pr.PDC != ivideo->detectedpdc)) अणु
				prपूर्णांकk(KERN_INFO "sisfb: Using LCD PDC 0x%02x (for LCD=CRT2)\n",
					ivideo->SiS_Pr.PDC);
			पूर्ण
			अगर((ivideo->SiS_Pr.PDCA != -1) &&
			   (ivideo->SiS_Pr.PDCA != ivideo->detectedpdca)) अणु
				prपूर्णांकk(KERN_INFO "sisfb: Using LCD PDC1 0x%02x (for LCD=CRT1)\n",
				 ivideo->SiS_Pr.PDCA);
			पूर्ण
		पूर्ण

	पूर्ण
#पूर्ण_अगर
पूर्ण

/* -------------------- Memory manager routines ---------------------- */

अटल u32 sisfb_getheapstart(काष्ठा sis_video_info *ivideo)
अणु
	u32 ret = ivideo->sisfb_parm_mem * 1024;
	u32 maxoffs = ivideo->video_size - ivideo->hwcursor_size - ivideo->cmdQueueSize;
	u32 def;

	/* Calculate heap start = end of memory क्रम console
	 *
	 * CCCCCCCCDDDDDDDDDDDDDDDDDDDDDDDDDDDDHHHHQQQQQQQQQQ
	 * C = console, D = heap, H = HWCursor, Q = cmd-queue
	 *
	 * On 76x in UMA+LFB mode, the layout is as follows:
	 * DDDDDDDDDDDCCCCCCCCCCCCCCCCCCCCCCCCHHHHQQQQQQQQQQQ
	 * where the heap is the entire UMA area, eventually
	 * पूर्णांकo the LFB area अगर the given mem parameter is
	 * higher than the size of the UMA memory.
	 *
	 * Basically given by "mem" parameter
	 *
	 * maximum = videosize - cmd_queue - hwcursor
	 *           (results in a heap of size 0)
	 * शेष = SiS 300: depends on videosize
	 *           SiS 315/330/340/XGI: 32k below max
	 */

	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		अगर(ivideo->video_size > 0x1000000) अणु
			def = 0xc00000;
		पूर्ण अन्यथा अगर(ivideo->video_size > 0x800000) अणु
			def = 0x800000;
		पूर्ण अन्यथा अणु
			def = 0x400000;
		पूर्ण
	पूर्ण अन्यथा अगर(ivideo->UMAsize && ivideo->LFBsize) अणु
		ret = def = 0;
	पूर्ण अन्यथा अणु
		def = maxoffs - 0x8000;
	पूर्ण

	/* Use शेष क्रम secondary card क्रम now (FIXME) */
	अगर((!ret) || (ret > maxoffs) || (ivideo->cardnumber != 0))
		ret = def;

	वापस ret;
पूर्ण

अटल u32 sisfb_getheapsize(काष्ठा sis_video_info *ivideo)
अणु
	u32 max = ivideo->video_size - ivideo->hwcursor_size - ivideo->cmdQueueSize;
	u32 ret = 0;

	अगर(ivideo->UMAsize && ivideo->LFBsize) अणु
		अगर( (!ivideo->sisfb_parm_mem)			||
		    ((ivideo->sisfb_parm_mem * 1024) > max)	||
		    ((max - (ivideo->sisfb_parm_mem * 1024)) < ivideo->UMAsize) ) अणु
			ret = ivideo->UMAsize;
			max -= ivideo->UMAsize;
		पूर्ण अन्यथा अणु
			ret = max - (ivideo->sisfb_parm_mem * 1024);
			max = ivideo->sisfb_parm_mem * 1024;
		पूर्ण
		ivideo->video_offset = ret;
		ivideo->sisfb_mem = max;
	पूर्ण अन्यथा अणु
		ret = max - ivideo->heapstart;
		ivideo->sisfb_mem = ivideo->heapstart;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisfb_heap_init(काष्ठा sis_video_info *ivideo)
अणु
	काष्ठा SIS_OH *poh;

	ivideo->video_offset = 0;
	अगर(ivideo->sisfb_parm_mem) अणु
		अगर( (ivideo->sisfb_parm_mem < (2 * 1024 * 1024)) ||
		    (ivideo->sisfb_parm_mem > ivideo->video_size) ) अणु
			ivideo->sisfb_parm_mem = 0;
		पूर्ण
	पूर्ण

	ivideo->heapstart = sisfb_getheapstart(ivideo);
	ivideo->sisfb_heap_size = sisfb_getheapsize(ivideo);

	ivideo->sisfb_heap_start = ivideo->video_vbase + ivideo->heapstart;
	ivideo->sisfb_heap_end   = ivideo->sisfb_heap_start + ivideo->sisfb_heap_size;

	prपूर्णांकk(KERN_INFO "sisfb: Memory heap starting at %dK, size %dK\n",
		(पूर्णांक)(ivideo->heapstart / 1024), (पूर्णांक)(ivideo->sisfb_heap_size / 1024));

	ivideo->sisfb_heap.vinfo = ivideo;

	ivideo->sisfb_heap.poha_chain = शून्य;
	ivideo->sisfb_heap.poh_मुक्तlist = शून्य;

	poh = sisfb_poh_new_node(&ivideo->sisfb_heap);
	अगर(poh == शून्य)
		वापस 1;

	poh->poh_next = &ivideo->sisfb_heap.oh_मुक्त;
	poh->poh_prev = &ivideo->sisfb_heap.oh_मुक्त;
	poh->size = ivideo->sisfb_heap_size;
	poh->offset = ivideo->heapstart;

	ivideo->sisfb_heap.oh_मुक्त.poh_next = poh;
	ivideo->sisfb_heap.oh_मुक्त.poh_prev = poh;
	ivideo->sisfb_heap.oh_मुक्त.size = 0;
	ivideo->sisfb_heap.max_मुक्तsize = poh->size;

	ivideo->sisfb_heap.oh_used.poh_next = &ivideo->sisfb_heap.oh_used;
	ivideo->sisfb_heap.oh_used.poh_prev = &ivideo->sisfb_heap.oh_used;
	ivideo->sisfb_heap.oh_used.size = SENTINEL;

	अगर(ivideo->cardnumber == 0) अणु
		/* For the first card, make this heap the "global" one
		 * क्रम old DRM (which could handle only one card)
		 */
		sisfb_heap = &ivideo->sisfb_heap;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा SIS_OH *
sisfb_poh_new_node(काष्ठा SIS_HEAP *memheap)
अणु
	काष्ठा SIS_OHALLOC	*poha;
	काष्ठा SIS_OH		*poh;
	अचिन्हित दीर्घ		cOhs;
	पूर्णांक			i;

	अगर(memheap->poh_मुक्तlist == शून्य) अणु
		poha = kदो_स्मृति(SIS_OH_ALLOC_SIZE, GFP_KERNEL);
		अगर(!poha)
			वापस शून्य;

		poha->poha_next = memheap->poha_chain;
		memheap->poha_chain = poha;

		cOhs = (SIS_OH_ALLOC_SIZE - माप(काष्ठा SIS_OHALLOC)) / माप(काष्ठा SIS_OH) + 1;

		poh = &poha->aoh[0];
		क्रम(i = cOhs - 1; i != 0; i--) अणु
			poh->poh_next = poh + 1;
			poh = poh + 1;
		पूर्ण

		poh->poh_next = शून्य;
		memheap->poh_मुक्तlist = &poha->aoh[0];
	पूर्ण

	poh = memheap->poh_मुक्तlist;
	memheap->poh_मुक्तlist = poh->poh_next;

	वापस poh;
पूर्ण

अटल काष्ठा SIS_OH *
sisfb_poh_allocate(काष्ठा SIS_HEAP *memheap, u32 size)
अणु
	काष्ठा SIS_OH	*pohThis;
	काष्ठा SIS_OH	*pohRoot;
	पूर्णांक		bAllocated = 0;

	अगर(size > memheap->max_मुक्तsize) अणु
		DPRINTK("sisfb: Can't allocate %dk video memory\n",
			(अचिन्हित पूर्णांक) size / 1024);
		वापस शून्य;
	पूर्ण

	pohThis = memheap->oh_मुक्त.poh_next;

	जबतक(pohThis != &memheap->oh_मुक्त) अणु
		अगर(size <= pohThis->size) अणु
			bAllocated = 1;
			अवरोध;
		पूर्ण
		pohThis = pohThis->poh_next;
	पूर्ण

	अगर(!bAllocated) अणु
		DPRINTK("sisfb: Can't allocate %dk video memory\n",
			(अचिन्हित पूर्णांक) size / 1024);
		वापस शून्य;
	पूर्ण

	अगर(size == pohThis->size) अणु
		pohRoot = pohThis;
		sisfb_delete_node(pohThis);
	पूर्ण अन्यथा अणु
		pohRoot = sisfb_poh_new_node(memheap);
		अगर(pohRoot == शून्य)
			वापस शून्य;

		pohRoot->offset = pohThis->offset;
		pohRoot->size = size;

		pohThis->offset += size;
		pohThis->size -= size;
	पूर्ण

	memheap->max_मुक्तsize -= size;

	pohThis = &memheap->oh_used;
	sisfb_insert_node(pohThis, pohRoot);

	वापस pohRoot;
पूर्ण

अटल व्योम
sisfb_delete_node(काष्ठा SIS_OH *poh)
अणु
	poh->poh_prev->poh_next = poh->poh_next;
	poh->poh_next->poh_prev = poh->poh_prev;
पूर्ण

अटल व्योम
sisfb_insert_node(काष्ठा SIS_OH *pohList, काष्ठा SIS_OH *poh)
अणु
	काष्ठा SIS_OH *pohTemp = pohList->poh_next;

	pohList->poh_next = poh;
	pohTemp->poh_prev = poh;

	poh->poh_prev = pohList;
	poh->poh_next = pohTemp;
पूर्ण

अटल काष्ठा SIS_OH *
sisfb_poh_मुक्त(काष्ठा SIS_HEAP *memheap, u32 base)
अणु
	काष्ठा SIS_OH *pohThis;
	काष्ठा SIS_OH *poh_मुक्तd;
	काष्ठा SIS_OH *poh_prev;
	काष्ठा SIS_OH *poh_next;
	u32    ulUpper;
	u32    ulLower;
	पूर्णांक    foundNode = 0;

	poh_मुक्तd = memheap->oh_used.poh_next;

	जबतक(poh_मुक्तd != &memheap->oh_used) अणु
		अगर(poh_मुक्तd->offset == base) अणु
			foundNode = 1;
			अवरोध;
		पूर्ण

		poh_मुक्तd = poh_मुक्तd->poh_next;
	पूर्ण

	अगर(!foundNode)
		वापस शून्य;

	memheap->max_मुक्तsize += poh_मुक्तd->size;

	poh_prev = poh_next = शून्य;
	ulUpper = poh_मुक्तd->offset + poh_मुक्तd->size;
	ulLower = poh_मुक्तd->offset;

	pohThis = memheap->oh_मुक्त.poh_next;

	जबतक(pohThis != &memheap->oh_मुक्त) अणु
		अगर(pohThis->offset == ulUpper) अणु
			poh_next = pohThis;
		पूर्ण अन्यथा अगर((pohThis->offset + pohThis->size) == ulLower) अणु
			poh_prev = pohThis;
		पूर्ण
		pohThis = pohThis->poh_next;
	पूर्ण

	sisfb_delete_node(poh_मुक्तd);

	अगर(poh_prev && poh_next) अणु
		poh_prev->size += (poh_मुक्तd->size + poh_next->size);
		sisfb_delete_node(poh_next);
		sisfb_मुक्त_node(memheap, poh_मुक्तd);
		sisfb_मुक्त_node(memheap, poh_next);
		वापस poh_prev;
	पूर्ण

	अगर(poh_prev) अणु
		poh_prev->size += poh_मुक्तd->size;
		sisfb_मुक्त_node(memheap, poh_मुक्तd);
		वापस poh_prev;
	पूर्ण

	अगर(poh_next) अणु
		poh_next->size += poh_मुक्तd->size;
		poh_next->offset = poh_मुक्तd->offset;
		sisfb_मुक्त_node(memheap, poh_मुक्तd);
		वापस poh_next;
	पूर्ण

	sisfb_insert_node(&memheap->oh_मुक्त, poh_मुक्तd);

	वापस poh_मुक्तd;
पूर्ण

अटल व्योम
sisfb_मुक्त_node(काष्ठा SIS_HEAP *memheap, काष्ठा SIS_OH *poh)
अणु
	अगर(poh == शून्य)
		वापस;

	poh->poh_next = memheap->poh_मुक्तlist;
	memheap->poh_मुक्तlist = poh;
पूर्ण

अटल व्योम
sis_पूर्णांक_दो_स्मृति(काष्ठा sis_video_info *ivideo, काष्ठा sis_memreq *req)
अणु
	काष्ठा SIS_OH *poh = शून्य;

	अगर((ivideo) && (ivideo->sisfb_id == SISFB_ID) && (!ivideo->havenoheap))
		poh = sisfb_poh_allocate(&ivideo->sisfb_heap, (u32)req->size);

	अगर(poh == शून्य) अणु
		req->offset = req->size = 0;
		DPRINTK("sisfb: Video RAM allocation failed\n");
	पूर्ण अन्यथा अणु
		req->offset = poh->offset;
		req->size = poh->size;
		DPRINTK("sisfb: Video RAM allocation succeeded: 0x%lx\n",
			(poh->offset + ivideo->video_vbase));
	पूर्ण
पूर्ण

व्योम
sis_दो_स्मृति(काष्ठा sis_memreq *req)
अणु
	काष्ठा sis_video_info *ivideo = sisfb_heap->vinfo;

	अगर(&ivideo->sisfb_heap == sisfb_heap)
		sis_पूर्णांक_दो_स्मृति(ivideo, req);
	अन्यथा
		req->offset = req->size = 0;
पूर्ण

व्योम
sis_दो_स्मृति_new(काष्ठा pci_dev *pdev, काष्ठा sis_memreq *req)
अणु
	काष्ठा sis_video_info *ivideo = pci_get_drvdata(pdev);

	sis_पूर्णांक_दो_स्मृति(ivideo, req);
पूर्ण

/* sis_मुक्त: u32 because "base" is offset inside video ram, can never be >4GB */

अटल व्योम
sis_पूर्णांक_मुक्त(काष्ठा sis_video_info *ivideo, u32 base)
अणु
	काष्ठा SIS_OH *poh;

	अगर((!ivideo) || (ivideo->sisfb_id != SISFB_ID) || (ivideo->havenoheap))
		वापस;

	poh = sisfb_poh_मुक्त(&ivideo->sisfb_heap, base);

	अगर(poh == शून्य) अणु
		DPRINTK("sisfb: sisfb_poh_free() failed at base 0x%x\n",
			(अचिन्हित पूर्णांक) base);
	पूर्ण
पूर्ण

व्योम
sis_मुक्त(u32 base)
अणु
	काष्ठा sis_video_info *ivideo = sisfb_heap->vinfo;

	sis_पूर्णांक_मुक्त(ivideo, base);
पूर्ण

व्योम
sis_मुक्त_new(काष्ठा pci_dev *pdev, u32 base)
अणु
	काष्ठा sis_video_info *ivideo = pci_get_drvdata(pdev);

	sis_पूर्णांक_मुक्त(ivideo, base);
पूर्ण

/* --------------------- SetMode routines ------------------------- */

अटल व्योम
sisfb_check_engine_and_sync(काष्ठा sis_video_info *ivideo)
अणु
	u8 cr30, cr31;

	/* Check अगर MMIO and engines are enabled,
	 * and sync in हाल they are. Can't use
	 * ivideo->accel here, as this might have
	 * been changed beक्रमe this is called.
	 */
	cr30 = SiS_GetReg(SISSR, IND_SIS_PCI_ADDRESS_SET);
	cr31 = SiS_GetReg(SISSR, IND_SIS_MODULE_ENABLE);
	/* MMIO and 2D/3D engine enabled? */
	अगर((cr30 & SIS_MEM_MAP_IO_ENABLE) && (cr31 & 0x42)) अणु
#अगर_घोषित CONFIG_FB_SIS_300
		अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
			/* Don't care about TurboQueue. It's
			 * enough to know that the engines
			 * are enabled
			 */
			sisfb_syncaccel(ivideo);
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
		अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
			/* Check that any queue mode is
			 * enabled, and that the queue
			 * is not in the state of "reset"
			 */
			cr30 = SiS_GetReg(SISSR, 0x26);
			अगर((cr30 & 0xe0) && (!(cr30 & 0x01))) अणु
				sisfb_syncaccel(ivideo);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम
sisfb_pre_seपंचांगode(काष्ठा sis_video_info *ivideo)
अणु
	u8 cr30 = 0, cr31 = 0, cr33 = 0, cr35 = 0, cr38 = 0;
	पूर्णांक tvregnum = 0;

	ivideo->currentvbflags &= (VB_VIDEOBRIDGE | VB_DISPTYPE_DISP2);

	SiS_SetReg(SISSR, 0x05, 0x86);

	cr31 = SiS_GetReg(SISCR, 0x31);
	cr31 &= ~0x60;
	cr31 |= 0x04;

	cr33 = ivideo->rate_idx & 0x0F;

#अगर_घोषित CONFIG_FB_SIS_315
	अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
	   अगर(ivideo->chip >= SIS_661) अणु
	      cr38 = SiS_GetReg(SISCR, 0x38);
	      cr38 &= ~0x07;  /* Clear LCDA/DualEdge and YPbPr bits */
	   पूर्ण अन्यथा अणु
	      tvregnum = 0x38;
	      cr38 = SiS_GetReg(SISCR, tvregnum);
	      cr38 &= ~0x3b;  /* Clear LCDA/DualEdge and YPbPr bits */
	   पूर्ण
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_300
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
	   tvregnum = 0x35;
	   cr38 = SiS_GetReg(SISCR, tvregnum);
	पूर्ण
#पूर्ण_अगर

	SiS_SetEnableDstn(&ivideo->SiS_Pr, false);
	SiS_SetEnableFstn(&ivideo->SiS_Pr, false);
	ivideo->curFSTN = ivideo->curDSTN = 0;

	चयन(ivideo->currentvbflags & VB_DISPTYPE_DISP2) अणु

	   हाल CRT2_TV:
	      cr38 &= ~0xc0;   /* Clear PAL-M / PAL-N bits */
	      अगर((ivideo->vbflags & TV_YPBPR) && (ivideo->vbflags2 & VB2_SISYPBPRBRIDGE)) अणु
#अगर_घोषित CONFIG_FB_SIS_315
		 अगर(ivideo->chip >= SIS_661) अणु
		    cr38 |= 0x04;
		    अगर(ivideo->vbflags & TV_YPBPR525P)       cr35 |= 0x20;
		    अन्यथा अगर(ivideo->vbflags & TV_YPBPR750P)  cr35 |= 0x40;
		    अन्यथा अगर(ivideo->vbflags & TV_YPBPR1080I) cr35 |= 0x60;
		    cr30 |= SIS_SIMULTANEOUS_VIEW_ENABLE;
		    cr35 &= ~0x01;
		    ivideo->currentvbflags |= (TV_YPBPR | (ivideo->vbflags & TV_YPBPRALL));
		 पूर्ण अन्यथा अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
		    cr30 |= (0x80 | SIS_SIMULTANEOUS_VIEW_ENABLE);
		    cr38 |= 0x08;
		    अगर(ivideo->vbflags & TV_YPBPR525P)       cr38 |= 0x10;
		    अन्यथा अगर(ivideo->vbflags & TV_YPBPR750P)  cr38 |= 0x20;
		    अन्यथा अगर(ivideo->vbflags & TV_YPBPR1080I) cr38 |= 0x30;
		    cr31 &= ~0x01;
		    ivideo->currentvbflags |= (TV_YPBPR | (ivideo->vbflags & TV_YPBPRALL));
		 पूर्ण
#पूर्ण_अगर
	      पूर्ण अन्यथा अगर((ivideo->vbflags & TV_HIVISION) &&
				(ivideo->vbflags2 & VB2_SISHIVISIONBRIDGE)) अणु
		 अगर(ivideo->chip >= SIS_661) अणु
		    cr38 |= 0x04;
		    cr35 |= 0x60;
		 पूर्ण अन्यथा अणु
		    cr30 |= 0x80;
		 पूर्ण
		 cr30 |= SIS_SIMULTANEOUS_VIEW_ENABLE;
		 cr31 |= 0x01;
		 cr35 |= 0x01;
		 ivideo->currentvbflags |= TV_HIVISION;
	      पूर्ण अन्यथा अगर(ivideo->vbflags & TV_SCART) अणु
		 cr30 = (SIS_VB_OUTPUT_SCART | SIS_SIMULTANEOUS_VIEW_ENABLE);
		 cr31 |= 0x01;
		 cr35 |= 0x01;
		 ivideo->currentvbflags |= TV_SCART;
	      पूर्ण अन्यथा अणु
		 अगर(ivideo->vbflags & TV_SVIDEO) अणु
		    cr30 = (SIS_VB_OUTPUT_SVIDEO | SIS_SIMULTANEOUS_VIEW_ENABLE);
		    ivideo->currentvbflags |= TV_SVIDEO;
		 पूर्ण
		 अगर(ivideo->vbflags & TV_AVIDEO) अणु
		    cr30 = (SIS_VB_OUTPUT_COMPOSITE | SIS_SIMULTANEOUS_VIEW_ENABLE);
		    ivideo->currentvbflags |= TV_AVIDEO;
		 पूर्ण
	      पूर्ण
	      cr31 |= SIS_DRIVER_MODE;

	      अगर(ivideo->vbflags & (TV_AVIDEO | TV_SVIDEO)) अणु
		 अगर(ivideo->vbflags & TV_PAL) अणु
		    cr31 |= 0x01; cr35 |= 0x01;
		    ivideo->currentvbflags |= TV_PAL;
		    अगर(ivideo->vbflags & TV_PALM) अणु
		       cr38 |= 0x40; cr35 |= 0x04;
		       ivideo->currentvbflags |= TV_PALM;
		    पूर्ण अन्यथा अगर(ivideo->vbflags & TV_PALN) अणु
		       cr38 |= 0x80; cr35 |= 0x08;
		       ivideo->currentvbflags |= TV_PALN;
		    पूर्ण
		 पूर्ण अन्यथा अणु
		    cr31 &= ~0x01; cr35 &= ~0x01;
		    ivideo->currentvbflags |= TV_NTSC;
		    अगर(ivideo->vbflags & TV_NTSCJ) अणु
		       cr38 |= 0x40; cr35 |= 0x02;
		       ivideo->currentvbflags |= TV_NTSCJ;
		    पूर्ण
		 पूर्ण
	      पूर्ण
	      अवरोध;

	   हाल CRT2_LCD:
	      cr30  = (SIS_VB_OUTPUT_LCD | SIS_SIMULTANEOUS_VIEW_ENABLE);
	      cr31 |= SIS_DRIVER_MODE;
	      SiS_SetEnableDstn(&ivideo->SiS_Pr, ivideo->sisfb_dstn);
	      SiS_SetEnableFstn(&ivideo->SiS_Pr, ivideo->sisfb_fstn);
	      ivideo->curFSTN = ivideo->sisfb_fstn;
	      ivideo->curDSTN = ivideo->sisfb_dstn;
	      अवरोध;

	   हाल CRT2_VGA:
	      cr30 = (SIS_VB_OUTPUT_CRT2 | SIS_SIMULTANEOUS_VIEW_ENABLE);
	      cr31 |= SIS_DRIVER_MODE;
	      अगर(ivideo->sisfb_nocrt2rate) अणु
		 cr33 |= (sisbios_mode[ivideo->sisfb_mode_idx].rate_idx << 4);
	      पूर्ण अन्यथा अणु
		 cr33 |= ((ivideo->rate_idx & 0x0F) << 4);
	      पूर्ण
	      अवरोध;

	   शेष:	/* disable CRT2 */
	      cr30 = 0x00;
	      cr31 |= (SIS_DRIVER_MODE | SIS_VB_OUTPUT_DISABLE);
	पूर्ण

	SiS_SetReg(SISCR, 0x30, cr30);
	SiS_SetReg(SISCR, 0x33, cr33);

	अगर(ivideo->chip >= SIS_661) अणु
#अगर_घोषित CONFIG_FB_SIS_315
	   cr31 &= ~0x01;                          /* Clear PAL flag (now in CR35) */
	   SiS_SetRegANDOR(SISCR, 0x35, ~0x10, cr35); /* Leave overscan bit alone */
	   cr38 &= 0x07;                           /* Use only LCDA and HiVision/YPbPr bits */
	   SiS_SetRegANDOR(SISCR, 0x38, 0xf8, cr38);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर(ivideo->chip != SIS_300) अणु
	   SiS_SetReg(SISCR, tvregnum, cr38);
	पूर्ण
	SiS_SetReg(SISCR, 0x31, cr31);

	ivideo->SiS_Pr.SiS_UseOEM = ivideo->sisfb_useoem;

	sisfb_check_engine_and_sync(ivideo);
पूर्ण

/* Fix SR11 क्रम 661 and later */
#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
sisfb_fixup_SR11(काष्ठा sis_video_info *ivideo)
अणु
	u8  पंचांगpreg;

	अगर(ivideo->chip >= SIS_661) अणु
		पंचांगpreg = SiS_GetReg(SISSR, 0x11);
		अगर(पंचांगpreg & 0x20) अणु
			पंचांगpreg = SiS_GetReg(SISSR, 0x3e);
			पंचांगpreg = (पंचांगpreg + 1) & 0xff;
			SiS_SetReg(SISSR, 0x3e, पंचांगpreg);
			पंचांगpreg = SiS_GetReg(SISSR, 0x11);
		पूर्ण
		अगर(पंचांगpreg & 0xf0) अणु
			SiS_SetRegAND(SISSR, 0x11, 0x0f);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम
sisfb_set_TVxposoffset(काष्ठा sis_video_info *ivideo, पूर्णांक val)
अणु
	अगर(val > 32) val = 32;
	अगर(val < -32) val = -32;
	ivideo->tvxpos = val;

	अगर(ivideo->sisfblocked) वापस;
	अगर(!ivideo->modechanged) वापस;

	अगर(ivideo->currentvbflags & CRT2_TV) अणु

		अगर(ivideo->vbflags2 & VB2_CHRONTEL) अणु

			पूर्णांक x = ivideo->tvx;

			चयन(ivideo->chronteltype) अणु
			हाल 1:
				x += val;
				अगर(x < 0) x = 0;
				SiS_SetReg(SISSR, 0x05, 0x86);
				SiS_SetCH700x(&ivideo->SiS_Pr, 0x0a, (x & 0xff));
				SiS_SetCH70xxANDOR(&ivideo->SiS_Pr, 0x08, ((x & 0x0100) >> 7), 0xFD);
				अवरोध;
			हाल 2:
				/* Not supported by hardware */
				अवरोध;
			पूर्ण

		पूर्ण अन्यथा अगर(ivideo->vbflags2 & VB2_SISBRIDGE) अणु

			u8 p2_1f,p2_20,p2_2b,p2_42,p2_43;
			अचिन्हित लघु temp;

			p2_1f = ivideo->p2_1f;
			p2_20 = ivideo->p2_20;
			p2_2b = ivideo->p2_2b;
			p2_42 = ivideo->p2_42;
			p2_43 = ivideo->p2_43;

			temp = p2_1f | ((p2_20 & 0xf0) << 4);
			temp += (val * 2);
			p2_1f = temp & 0xff;
			p2_20 = (temp & 0xf00) >> 4;
			p2_2b = ((p2_2b & 0x0f) + (val * 2)) & 0x0f;
			temp = p2_43 | ((p2_42 & 0xf0) << 4);
			temp += (val * 2);
			p2_43 = temp & 0xff;
			p2_42 = (temp & 0xf00) >> 4;
			SiS_SetReg(SISPART2, 0x1f, p2_1f);
			SiS_SetRegANDOR(SISPART2, 0x20, 0x0F, p2_20);
			SiS_SetRegANDOR(SISPART2, 0x2b, 0xF0, p2_2b);
			SiS_SetRegANDOR(SISPART2, 0x42, 0x0F, p2_42);
			SiS_SetReg(SISPART2, 0x43, p2_43);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
sisfb_set_TVyposoffset(काष्ठा sis_video_info *ivideo, पूर्णांक val)
अणु
	अगर(val > 32) val = 32;
	अगर(val < -32) val = -32;
	ivideo->tvypos = val;

	अगर(ivideo->sisfblocked) वापस;
	अगर(!ivideo->modechanged) वापस;

	अगर(ivideo->currentvbflags & CRT2_TV) अणु

		अगर(ivideo->vbflags2 & VB2_CHRONTEL) अणु

			पूर्णांक y = ivideo->tvy;

			चयन(ivideo->chronteltype) अणु
			हाल 1:
				y -= val;
				अगर(y < 0) y = 0;
				SiS_SetReg(SISSR, 0x05, 0x86);
				SiS_SetCH700x(&ivideo->SiS_Pr, 0x0b, (y & 0xff));
				SiS_SetCH70xxANDOR(&ivideo->SiS_Pr, 0x08, ((y & 0x0100) >> 8), 0xFE);
				अवरोध;
			हाल 2:
				/* Not supported by hardware */
				अवरोध;
			पूर्ण

		पूर्ण अन्यथा अगर(ivideo->vbflags2 & VB2_SISBRIDGE) अणु

			अक्षर p2_01, p2_02;
			val /= 2;
			p2_01 = ivideo->p2_01;
			p2_02 = ivideo->p2_02;

			p2_01 += val;
			p2_02 += val;
			अगर(!(ivideo->currentvbflags & (TV_HIVISION | TV_YPBPR))) अणु
				जबतक((p2_01 <= 0) || (p2_02 <= 0)) अणु
					p2_01 += 2;
					p2_02 += 2;
				पूर्ण
			पूर्ण
			SiS_SetReg(SISPART2, 0x01, p2_01);
			SiS_SetReg(SISPART2, 0x02, p2_02);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
sisfb_post_seपंचांगode(काष्ठा sis_video_info *ivideo)
अणु
	bool crt1isoff = false;
	bool करोit = true;
#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
	u8 reg;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
	u8 reg1;
#पूर्ण_अगर

	SiS_SetReg(SISSR, 0x05, 0x86);

#अगर_घोषित CONFIG_FB_SIS_315
	sisfb_fixup_SR11(ivideo);
#पूर्ण_अगर

	/* Now we actually HAVE changed the display mode */
	ivideo->modechanged = 1;

	/* We can't चयन off CRT1 अगर bridge is in slave mode */
	अगर(ivideo->vbflags2 & VB2_VIDEOBRIDGE) अणु
		अगर(sisfb_bridgeisslave(ivideo)) करोit = false;
	पूर्ण अन्यथा
		ivideo->sisfb_crt1off = 0;

#अगर_घोषित CONFIG_FB_SIS_300
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		अगर((ivideo->sisfb_crt1off) && (करोit)) अणु
			crt1isoff = true;
			reg = 0x00;
		पूर्ण अन्यथा अणु
			crt1isoff = false;
			reg = 0x80;
		पूर्ण
		SiS_SetRegANDOR(SISCR, 0x17, 0x7f, reg);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
	अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
		अगर((ivideo->sisfb_crt1off) && (करोit)) अणु
			crt1isoff = true;
			reg  = 0x40;
			reg1 = 0xc0;
		पूर्ण अन्यथा अणु
			crt1isoff = false;
			reg  = 0x00;
			reg1 = 0x00;
		पूर्ण
		SiS_SetRegANDOR(SISCR, ivideo->SiS_Pr.SiS_MyCR63, ~0x40, reg);
		SiS_SetRegANDOR(SISSR, 0x1f, 0x3f, reg1);
	पूर्ण
#पूर्ण_अगर

	अगर(crt1isoff) अणु
		ivideo->currentvbflags &= ~VB_DISPTYPE_CRT1;
		ivideo->currentvbflags |= VB_SINGLE_MODE;
	पूर्ण अन्यथा अणु
		ivideo->currentvbflags |= VB_DISPTYPE_CRT1;
		अगर(ivideo->currentvbflags & VB_DISPTYPE_CRT2) अणु
			ivideo->currentvbflags |= VB_MIRROR_MODE;
		पूर्ण अन्यथा अणु
			ivideo->currentvbflags |= VB_SINGLE_MODE;
		पूर्ण
	पूर्ण

	SiS_SetRegAND(SISSR, IND_SIS_RAMDAC_CONTROL, ~0x04);

	अगर(ivideo->currentvbflags & CRT2_TV) अणु
		अगर(ivideo->vbflags2 & VB2_SISBRIDGE) अणु
			ivideo->p2_1f = SiS_GetReg(SISPART2, 0x1f);
			ivideo->p2_20 = SiS_GetReg(SISPART2, 0x20);
			ivideo->p2_2b = SiS_GetReg(SISPART2, 0x2b);
			ivideo->p2_42 = SiS_GetReg(SISPART2, 0x42);
			ivideo->p2_43 = SiS_GetReg(SISPART2, 0x43);
			ivideo->p2_01 = SiS_GetReg(SISPART2, 0x01);
			ivideo->p2_02 = SiS_GetReg(SISPART2, 0x02);
		पूर्ण अन्यथा अगर(ivideo->vbflags2 & VB2_CHRONTEL) अणु
			अगर(ivideo->chronteltype == 1) अणु
				ivideo->tvx = SiS_GetCH700x(&ivideo->SiS_Pr, 0x0a);
				ivideo->tvx |= (((SiS_GetCH700x(&ivideo->SiS_Pr, 0x08) & 0x02) >> 1) << 8);
				ivideo->tvy = SiS_GetCH700x(&ivideo->SiS_Pr, 0x0b);
				ivideo->tvy |= ((SiS_GetCH700x(&ivideo->SiS_Pr, 0x08) & 0x01) << 8);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर(ivideo->tvxpos) अणु
		sisfb_set_TVxposoffset(ivideo, ivideo->tvxpos);
	पूर्ण
	अगर(ivideo->tvypos) अणु
		sisfb_set_TVyposoffset(ivideo, ivideo->tvypos);
	पूर्ण

	/* Eventually sync engines */
	sisfb_check_engine_and_sync(ivideo);

	/* (Re-)Initialize chip engines */
	अगर(ivideo->accel) अणु
		sisfb_engine_init(ivideo);
	पूर्ण अन्यथा अणु
		ivideo->engineok = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
sisfb_reset_mode(काष्ठा sis_video_info *ivideo)
अणु
	अगर(sisfb_set_mode(ivideo, 0))
		वापस 1;

	sisfb_set_pitch(ivideo);
	sisfb_set_base_CRT1(ivideo, ivideo->current_base);
	sisfb_set_base_CRT2(ivideo, ivideo->current_base);

	वापस 0;
पूर्ण

अटल व्योम
sisfb_handle_command(काष्ठा sis_video_info *ivideo, काष्ठा sisfb_cmd *sisfb_command)
अणु
	पूर्णांक mycrt1off;

	चयन(sisfb_command->sisfb_cmd) अणु
	हाल SISFB_CMD_GETVBFLAGS:
		अगर(!ivideo->modechanged) अणु
			sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_EARLY;
		पूर्ण अन्यथा अणु
			sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_OK;
			sisfb_command->sisfb_result[1] = ivideo->currentvbflags;
			sisfb_command->sisfb_result[2] = ivideo->vbflags2;
		पूर्ण
		अवरोध;
	हाल SISFB_CMD_SWITCHCRT1:
		/* arg[0]: 0 = off, 1 = on, 99 = query */
		अगर(!ivideo->modechanged) अणु
			sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_EARLY;
		पूर्ण अन्यथा अगर(sisfb_command->sisfb_arg[0] == 99) अणु
			/* Query */
			sisfb_command->sisfb_result[1] = ivideo->sisfb_crt1off ? 0 : 1;
			sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_OK;
		पूर्ण अन्यथा अगर(ivideo->sisfblocked) अणु
			sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_LOCKED;
		पूर्ण अन्यथा अगर((!(ivideo->currentvbflags & CRT2_ENABLE)) &&
					(sisfb_command->sisfb_arg[0] == 0)) अणु
			sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_NOCRT2;
		पूर्ण अन्यथा अणु
			sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_OK;
			mycrt1off = sisfb_command->sisfb_arg[0] ? 0 : 1;
			अगर( ((ivideo->currentvbflags & VB_DISPTYPE_CRT1) && mycrt1off) ||
			    ((!(ivideo->currentvbflags & VB_DISPTYPE_CRT1)) && !mycrt1off) ) अणु
				ivideo->sisfb_crt1off = mycrt1off;
				अगर(sisfb_reset_mode(ivideo)) अणु
					sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_OTHER;
				पूर्ण
			पूर्ण
			sisfb_command->sisfb_result[1] = ivideo->sisfb_crt1off ? 0 : 1;
		पूर्ण
		अवरोध;
	/* more to come */
	शेष:
		sisfb_command->sisfb_result[0] = SISFB_CMD_ERR_UNKNOWN;
		prपूर्णांकk(KERN_ERR "sisfb: Unknown command 0x%x\n",
			sisfb_command->sisfb_cmd);
	पूर्ण
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init sisfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	sisfb_setशेषparms();

	अगर(!options || !(*options))
		वापस 0;

	जबतक((this_opt = strsep(&options, ",")) != शून्य) अणु

		अगर(!(*this_opt)) जारी;

		अगर(!strnहालcmp(this_opt, "off", 3)) अणु
			sisfb_off = 1;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "forcecrt2type:", 14)) अणु
			/* Need to check crt2 type first क्रम fstn/dstn */
			sisfb_search_crt2type(this_opt + 14);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "tvmode:",7)) अणु
			sisfb_search_tvstd(this_opt + 7);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "tvstandard:",11)) अणु
			sisfb_search_tvstd(this_opt + 11);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "mode:", 5)) अणु
			sisfb_search_mode(this_opt + 5, false);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "vesa:", 5)) अणु
			sisfb_search_vesamode(simple_म_से_अदीर्घ(this_opt + 5, शून्य, 0), false);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "rate:", 5)) अणु
			sisfb_parm_rate = simple_म_से_अदीर्घ(this_opt + 5, शून्य, 0);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "forcecrt1:", 10)) अणु
			sisfb_क्रमcecrt1 = (पूर्णांक)simple_म_से_अदीर्घ(this_opt + 10, शून्य, 0);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "mem:",4)) अणु
			sisfb_parm_mem = simple_म_से_अदीर्घ(this_opt + 4, शून्य, 0);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "pdc:", 4)) अणु
			sisfb_pdc = simple_म_से_अदीर्घ(this_opt + 4, शून्य, 0);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "pdc1:", 5)) अणु
			sisfb_pdca = simple_म_से_अदीर्घ(this_opt + 5, शून्य, 0);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "noaccel", 7)) अणु
			sisfb_accel = 0;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "accel", 5)) अणु
			sisfb_accel = -1;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "noypan", 6)) अणु
			sisfb_ypan = 0;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "ypan", 4)) अणु
			sisfb_ypan = -1;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "nomax", 5)) अणु
			sisfb_max = 0;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "max", 3)) अणु
			sisfb_max = -1;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "userom:", 7)) अणु
			sisfb_userom = (पूर्णांक)simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "useoem:", 7)) अणु
			sisfb_useoem = (पूर्णांक)simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "nocrt2rate", 10)) अणु
			sisfb_nocrt2rate = 1;
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "scalelcd:", 9)) अणु
			अचिन्हित दीर्घ temp = 2;
			temp = simple_म_से_अदीर्घ(this_opt + 9, शून्य, 0);
			अगर((temp == 0) || (temp == 1)) अणु
			   sisfb_scalelcd = temp ^ 1;
			पूर्ण
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "tvxposoffset:", 13)) अणु
			पूर्णांक temp = 0;
			temp = (पूर्णांक)simple_म_से_दीर्घ(this_opt + 13, शून्य, 0);
			अगर((temp >= -32) && (temp <= 32)) अणु
			   sisfb_tvxposoffset = temp;
			पूर्ण
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "tvyposoffset:", 13)) अणु
			पूर्णांक temp = 0;
			temp = (पूर्णांक)simple_म_से_दीर्घ(this_opt + 13, शून्य, 0);
			अगर((temp >= -32) && (temp <= 32)) अणु
			   sisfb_tvyposoffset = temp;
			पूर्ण
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "specialtiming:", 14)) अणु
			sisfb_search_specialtiming(this_opt + 14);
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "lvdshl:", 7)) अणु
			पूर्णांक temp = 4;
			temp = simple_म_से_अदीर्घ(this_opt + 7, शून्य, 0);
			अगर((temp >= 0) && (temp <= 3)) अणु
			   sisfb_lvdshl = temp;
			पूर्ण
		पूर्ण अन्यथा अगर(this_opt[0] >= '0' && this_opt[0] <= '9') अणु
			sisfb_search_mode(this_opt, true);
#अगर !defined(__i386__) && !defined(__x86_64__)
		पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "resetcard", 9)) अणु
			sisfb_resetcard = 1;
	        पूर्ण अन्यथा अगर(!strnहालcmp(this_opt, "videoram:", 9)) अणु
			sisfb_videoram = simple_म_से_अदीर्घ(this_opt + 9, शून्य, 0);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO "sisfb: Invalid option %s\n", this_opt);
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sisfb_check_rom(व्योम __iomem *rom_base,
			   काष्ठा sis_video_info *ivideo)
अणु
	व्योम __iomem *rom;
	पूर्णांक romptr;

	अगर((पढ़ोb(rom_base) != 0x55) || (पढ़ोb(rom_base + 1) != 0xaa))
		वापस 0;

	romptr = (पढ़ोb(rom_base + 0x18) | (पढ़ोb(rom_base + 0x19) << 8));
	अगर(romptr > (0x10000 - 8))
		वापस 0;

	rom = rom_base + romptr;

	अगर((पढ़ोb(rom)     != 'P') || (readb(rom + 1) != 'C') ||
	   (पढ़ोb(rom + 2) != 'I') || (readb(rom + 3) != 'R'))
		वापस 0;

	अगर((पढ़ोb(rom + 4) | (पढ़ोb(rom + 5) << 8)) != ivideo->chip_venकरोr)
		वापस 0;

	अगर((पढ़ोb(rom + 6) | (पढ़ोb(rom + 7) << 8)) != ivideo->chip_id)
		वापस 0;

	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर *sisfb_find_rom(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sis_video_info *ivideo = pci_get_drvdata(pdev);
	व्योम __iomem *rom_base;
	अचिन्हित अक्षर *myrombase = शून्य;
	माप_प्रकार romsize;

	/* First, try the official pci ROM functions (except
	 * on पूर्णांकegrated chipsets which have no ROM).
	 */

	अगर(!ivideo->nbridge) अणु

		अगर((rom_base = pci_map_rom(pdev, &romsize))) अणु

			अगर(sisfb_check_rom(rom_base, ivideo)) अणु

				अगर((myrombase = vदो_स्मृति(65536))) अणु
					स_नकल_fromio(myrombase, rom_base,
							(romsize > 65536) ? 65536 : romsize);
				पूर्ण
			पूर्ण
			pci_unmap_rom(pdev, rom_base);
		पूर्ण
	पूर्ण

	अगर(myrombase) वापस myrombase;

	/* Otherwise करो it the conventional way. */

#अगर defined(__i386__) || defined(__x86_64__)
	अणु
		u32 temp;

		क्रम (temp = 0x000c0000; temp < 0x000f0000; temp += 0x00001000) अणु

			rom_base = ioremap(temp, 65536);
			अगर (!rom_base)
				जारी;

			अगर (!sisfb_check_rom(rom_base, ivideo)) अणु
				iounmap(rom_base);
				जारी;
			पूर्ण

			अगर ((myrombase = vदो_स्मृति(65536)))
				स_नकल_fromio(myrombase, rom_base, 65536);

			iounmap(rom_base);
			अवरोध;

		पूर्ण

	पूर्ण
#पूर्ण_अगर

	वापस myrombase;
पूर्ण

अटल व्योम sisfb_post_map_vram(काष्ठा sis_video_info *ivideo,
				अचिन्हित पूर्णांक *mapsize, अचिन्हित पूर्णांक min)
अणु
	अगर (*mapsize < (min << 20))
		वापस;

	ivideo->video_vbase = ioremap_wc(ivideo->video_base, (*mapsize));

	अगर(!ivideo->video_vbase) अणु
		prपूर्णांकk(KERN_ERR
			"sisfb: Unable to map maximum video RAM for size detection\n");
		(*mapsize) >>= 1;
		जबतक((!(ivideo->video_vbase = ioremap_wc(ivideo->video_base, (*mapsize))))) अणु
			(*mapsize) >>= 1;
			अगर((*mapsize) < (min << 20))
				अवरोध;
		पूर्ण
		अगर(ivideo->video_vbase) अणु
			prपूर्णांकk(KERN_ERR
				"sisfb: Video RAM size detection limited to %dMB\n",
				(पूर्णांक)((*mapsize) >> 20));
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_FB_SIS_300
अटल पूर्णांक sisfb_post_300_buswidth(काष्ठा sis_video_info *ivideo)
अणु
	व्योम __iomem *FBAddress = ivideo->video_vbase;
	अचिन्हित लघु temp;
	अचिन्हित अक्षर reg;
	पूर्णांक i, j;

	SiS_SetRegAND(SISSR, 0x15, 0xFB);
	SiS_SetRegOR(SISSR, 0x15, 0x04);
	SiS_SetReg(SISSR, 0x13, 0x00);
	SiS_SetReg(SISSR, 0x14, 0xBF);

	क्रम(i = 0; i < 2; i++) अणु
		temp = 0x1234;
		क्रम(j = 0; j < 4; j++) अणु
			ग_लिखोw(temp, FBAddress);
			अगर(पढ़ोw(FBAddress) == temp)
				अवरोध;
			SiS_SetRegOR(SISSR, 0x3c, 0x01);
			reg = SiS_GetReg(SISSR, 0x05);
			reg = SiS_GetReg(SISSR, 0x05);
			SiS_SetRegAND(SISSR, 0x3c, 0xfe);
			reg = SiS_GetReg(SISSR, 0x05);
			reg = SiS_GetReg(SISSR, 0x05);
			temp++;
		पूर्ण
	पूर्ण

	ग_लिखोl(0x01234567L, FBAddress);
	ग_लिखोl(0x456789ABL, (FBAddress + 4));
	ग_लिखोl(0x89ABCDEFL, (FBAddress + 8));
	ग_लिखोl(0xCDEF0123L, (FBAddress + 12));

	reg = SiS_GetReg(SISSR, 0x3b);
	अगर(reg & 0x01) अणु
		अगर(पढ़ोl((FBAddress + 12)) == 0xCDEF0123L)
			वापस 4;	/* Channel A 128bit */
	पूर्ण

	अगर(पढ़ोl((FBAddress + 4)) == 0x456789ABL)
		वापस 2;		/* Channel B 64bit */

	वापस 1;			/* 32bit */
पूर्ण

अटल स्थिर अचिन्हित लघु SiS_DRAMType[17][5] = अणु
	अणु0x0C,0x0A,0x02,0x40,0x39पूर्ण,
	अणु0x0D,0x0A,0x01,0x40,0x48पूर्ण,
	अणु0x0C,0x09,0x02,0x20,0x35पूर्ण,
	अणु0x0D,0x09,0x01,0x20,0x44पूर्ण,
	अणु0x0C,0x08,0x02,0x10,0x31पूर्ण,
	अणु0x0D,0x08,0x01,0x10,0x40पूर्ण,
	अणु0x0C,0x0A,0x01,0x20,0x34पूर्ण,
	अणु0x0C,0x09,0x01,0x08,0x32पूर्ण,
	अणु0x0B,0x08,0x02,0x08,0x21पूर्ण,
	अणु0x0C,0x08,0x01,0x08,0x30पूर्ण,
	अणु0x0A,0x08,0x02,0x04,0x11पूर्ण,
	अणु0x0B,0x0A,0x01,0x10,0x28पूर्ण,
	अणु0x09,0x08,0x02,0x02,0x01पूर्ण,
	अणु0x0B,0x09,0x01,0x08,0x24पूर्ण,
	अणु0x0B,0x08,0x01,0x04,0x20पूर्ण,
	अणु0x0A,0x08,0x01,0x02,0x10पूर्ण,
	अणु0x09,0x08,0x01,0x01,0x00पूर्ण
पूर्ण;

अटल पूर्णांक sisfb_post_300_rwtest(काष्ठा sis_video_info *ivideo, पूर्णांक iteration,
				 पूर्णांक buswidth, पूर्णांक PseuकरोRankCapacity,
				 पूर्णांक PseuकरोAdrPinCount, अचिन्हित पूर्णांक mapsize)
अणु
	व्योम __iomem *FBAddr = ivideo->video_vbase;
	अचिन्हित लघु sr14;
	अचिन्हित पूर्णांक k, RankCapacity, PageCapacity, BankNumHigh, BankNumMid;
	अचिन्हित पूर्णांक PhysicalAdrOtherPage, PhysicalAdrHigh, PhysicalAdrHalfPage;

	 क्रम(k = 0; k < ARRAY_SIZE(SiS_DRAMType); k++) अणु

		RankCapacity = buswidth * SiS_DRAMType[k][3];

		अगर(RankCapacity != PseuकरोRankCapacity)
			जारी;

		अगर((SiS_DRAMType[k][2] + SiS_DRAMType[k][0]) > PseuकरोAdrPinCount)
			जारी;

		BankNumHigh = RankCapacity * 16 * iteration - 1;
		अगर(iteration == 3) अणु             /* Rank No */
			BankNumMid  = RankCapacity * 16 - 1;
		पूर्ण अन्यथा अणु
			BankNumMid  = RankCapacity * 16 * iteration / 2 - 1;
		पूर्ण

		PageCapacity = (1 << SiS_DRAMType[k][1]) * buswidth * 4;
		PhysicalAdrHigh = BankNumHigh;
		PhysicalAdrHalfPage = (PageCapacity / 2 + PhysicalAdrHigh) % PageCapacity;
		PhysicalAdrOtherPage = PageCapacity * SiS_DRAMType[k][2] + PhysicalAdrHigh;

		SiS_SetRegAND(SISSR, 0x15, 0xFB); /* Test */
		SiS_SetRegOR(SISSR, 0x15, 0x04);  /* Test */
		sr14 = (SiS_DRAMType[k][3] * buswidth) - 1;
		अगर(buswidth == 4)      sr14 |= 0x80;
		अन्यथा अगर(buswidth == 2) sr14 |= 0x40;
		SiS_SetReg(SISSR, 0x13, SiS_DRAMType[k][4]);
		SiS_SetReg(SISSR, 0x14, sr14);

		BankNumHigh <<= 16;
		BankNumMid <<= 16;

		अगर((BankNumHigh + PhysicalAdrHigh      >= mapsize) ||
		   (BankNumMid  + PhysicalAdrHigh      >= mapsize) ||
		   (BankNumHigh + PhysicalAdrHalfPage  >= mapsize) ||
		   (BankNumHigh + PhysicalAdrOtherPage >= mapsize))
			जारी;

		/* Write data */
		ग_लिखोw(((अचिन्हित लघु)PhysicalAdrHigh),
				(FBAddr + BankNumHigh + PhysicalAdrHigh));
		ग_लिखोw(((अचिन्हित लघु)BankNumMid),
				(FBAddr + BankNumMid  + PhysicalAdrHigh));
		ग_लिखोw(((अचिन्हित लघु)PhysicalAdrHalfPage),
				(FBAddr + BankNumHigh + PhysicalAdrHalfPage));
		ग_लिखोw(((अचिन्हित लघु)PhysicalAdrOtherPage),
				(FBAddr + BankNumHigh + PhysicalAdrOtherPage));

		/* Read data */
		अगर(पढ़ोw(FBAddr + BankNumHigh + PhysicalAdrHigh) == PhysicalAdrHigh)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sisfb_post_300_ramsize(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक mapsize)
अणु
	काष्ठा	sis_video_info *ivideo = pci_get_drvdata(pdev);
	पूर्णांक	i, j, buswidth;
	पूर्णांक	PseuकरोRankCapacity, PseuकरोAdrPinCount;

	buswidth = sisfb_post_300_buswidth(ivideo);

	क्रम(i = 6; i >= 0; i--) अणु
		PseuकरोRankCapacity = 1 << i;
		क्रम(j = 4; j >= 1; j--) अणु
			PseuकरोAdrPinCount = 15 - j;
			अगर((PseuकरोRankCapacity * j) <= 64) अणु
				अगर(sisfb_post_300_rwtest(ivideo,
						j,
						buswidth,
						PseuकरोRankCapacity,
						PseuकरोAdrPinCount,
						mapsize))
					वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sisfb_post_sis300(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sis_video_info *ivideo = pci_get_drvdata(pdev);
	अचिन्हित अक्षर *bios = ivideo->SiS_Pr.VirtualRomBase;
	u8  reg, v1, v2, v3, v4, v5, v6, v7, v8;
	u16 index, rindex, memtype = 0;
	अचिन्हित पूर्णांक mapsize;

	अगर(!ivideo->SiS_Pr.UseROM)
		bios = शून्य;

	SiS_SetReg(SISSR, 0x05, 0x86);

	अगर(bios) अणु
		अगर(bios[0x52] & 0x80) अणु
			memtype = bios[0x52];
		पूर्ण अन्यथा अणु
			memtype = SiS_GetReg(SISSR, 0x3a);
		पूर्ण
		memtype &= 0x07;
	पूर्ण

	v3 = 0x80; v6 = 0x80;
	अगर(ivideo->revision_id <= 0x13) अणु
		v1 = 0x44; v2 = 0x42;
		v4 = 0x44; v5 = 0x42;
	पूर्ण अन्यथा अणु
		v1 = 0x68; v2 = 0x43; /* Assume 125Mhz MCLK */
		v4 = 0x68; v5 = 0x43; /* Assume 125Mhz ECLK */
		अगर(bios) अणु
			index = memtype * 5;
			rindex = index + 0x54;
			v1 = bios[rindex++];
			v2 = bios[rindex++];
			v3 = bios[rindex++];
			rindex = index + 0x7c;
			v4 = bios[rindex++];
			v5 = bios[rindex++];
			v6 = bios[rindex++];
		पूर्ण
	पूर्ण
	SiS_SetReg(SISSR, 0x28, v1);
	SiS_SetReg(SISSR, 0x29, v2);
	SiS_SetReg(SISSR, 0x2a, v3);
	SiS_SetReg(SISSR, 0x2e, v4);
	SiS_SetReg(SISSR, 0x2f, v5);
	SiS_SetReg(SISSR, 0x30, v6);

	v1 = 0x10;
	अगर(bios)
		v1 = bios[0xa4];
	SiS_SetReg(SISSR, 0x07, v1);       /* DAC speed */

	SiS_SetReg(SISSR, 0x11, 0x0f);     /* DDC, घातer save */

	v1 = 0x01; v2 = 0x43; v3 = 0x1e; v4 = 0x2a;
	v5 = 0x06; v6 = 0x00; v7 = 0x00; v8 = 0x00;
	अगर(bios) अणु
		memtype += 0xa5;
		v1 = bios[memtype];
		v2 = bios[memtype + 8];
		v3 = bios[memtype + 16];
		v4 = bios[memtype + 24];
		v5 = bios[memtype + 32];
		v6 = bios[memtype + 40];
		v7 = bios[memtype + 48];
		v8 = bios[memtype + 56];
	पूर्ण
	अगर(ivideo->revision_id >= 0x80)
		v3 &= 0xfd;
	SiS_SetReg(SISSR, 0x15, v1);       /* Ram type (assuming 0, BIOS 0xa5 step 8) */
	SiS_SetReg(SISSR, 0x16, v2);
	SiS_SetReg(SISSR, 0x17, v3);
	SiS_SetReg(SISSR, 0x18, v4);
	SiS_SetReg(SISSR, 0x19, v5);
	SiS_SetReg(SISSR, 0x1a, v6);
	SiS_SetReg(SISSR, 0x1b, v7);
	SiS_SetReg(SISSR, 0x1c, v8);	   /* ---- */
	SiS_SetRegAND(SISSR, 0x15, 0xfb);
	SiS_SetRegOR(SISSR, 0x15, 0x04);
	अगर(bios) अणु
		अगर(bios[0x53] & 0x02) अणु
			SiS_SetRegOR(SISSR, 0x19, 0x20);
		पूर्ण
	पूर्ण
	v1 = 0x04;			   /* DAC pedestal (BIOS 0xe5) */
	अगर(ivideo->revision_id >= 0x80)
		v1 |= 0x01;
	SiS_SetReg(SISSR, 0x1f, v1);
	SiS_SetReg(SISSR, 0x20, 0xa4);     /* linear & relocated io & disable a0000 */
	v1 = 0xf6; v2 = 0x0d; v3 = 0x00;
	अगर(bios) अणु
		v1 = bios[0xe8];
		v2 = bios[0xe9];
		v3 = bios[0xea];
	पूर्ण
	SiS_SetReg(SISSR, 0x23, v1);
	SiS_SetReg(SISSR, 0x24, v2);
	SiS_SetReg(SISSR, 0x25, v3);
	SiS_SetReg(SISSR, 0x21, 0x84);
	SiS_SetReg(SISSR, 0x22, 0x00);
	SiS_SetReg(SISCR, 0x37, 0x00);
	SiS_SetRegOR(SISPART1, 0x24, 0x01);   /* unlock crt2 */
	SiS_SetReg(SISPART1, 0x00, 0x00);
	v1 = 0x40; v2 = 0x11;
	अगर(bios) अणु
		v1 = bios[0xec];
		v2 = bios[0xeb];
	पूर्ण
	SiS_SetReg(SISPART1, 0x02, v1);

	अगर(ivideo->revision_id >= 0x80)
		v2 &= ~0x01;

	reg = SiS_GetReg(SISPART4, 0x00);
	अगर((reg == 1) || (reg == 2)) अणु
		SiS_SetReg(SISCR, 0x37, 0x02);
		SiS_SetReg(SISPART2, 0x00, 0x1c);
		v4 = 0x00; v5 = 0x00; v6 = 0x10;
		अगर(ivideo->SiS_Pr.UseROM) अणु
			v4 = bios[0xf5];
			v5 = bios[0xf6];
			v6 = bios[0xf7];
		पूर्ण
		SiS_SetReg(SISPART4, 0x0d, v4);
		SiS_SetReg(SISPART4, 0x0e, v5);
		SiS_SetReg(SISPART4, 0x10, v6);
		SiS_SetReg(SISPART4, 0x0f, 0x3f);
		reg = SiS_GetReg(SISPART4, 0x01);
		अगर(reg >= 0xb0) अणु
			reg = SiS_GetReg(SISPART4, 0x23);
			reg &= 0x20;
			reg <<= 1;
			SiS_SetReg(SISPART4, 0x23, reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		v2 &= ~0x10;
	पूर्ण
	SiS_SetReg(SISSR, 0x32, v2);

	SiS_SetRegAND(SISPART1, 0x24, 0xfe);  /* Lock CRT2 */

	reg = SiS_GetReg(SISSR, 0x16);
	reg &= 0xc3;
	SiS_SetReg(SISCR, 0x35, reg);
	SiS_SetReg(SISCR, 0x83, 0x00);
#अगर !defined(__i386__) && !defined(__x86_64__)
	अगर(sisfb_videoram) अणु
		SiS_SetReg(SISSR, 0x13, 0x28);  /* ? */
		reg = ((sisfb_videoram >> 10) - 1) | 0x40;
		SiS_SetReg(SISSR, 0x14, reg);
	पूर्ण अन्यथा अणु
#पूर्ण_अगर
		/* Need to map max FB size क्रम finding out about RAM size */
		mapsize = ivideo->video_size;
		sisfb_post_map_vram(ivideo, &mapsize, 4);

		अगर(ivideo->video_vbase) अणु
			sisfb_post_300_ramsize(pdev, mapsize);
			iounmap(ivideo->video_vbase);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG
				"sisfb: Failed to map memory for size detection, assuming 8MB\n");
			SiS_SetReg(SISSR, 0x13, 0x28);  /* ? */
			SiS_SetReg(SISSR, 0x14, 0x47);  /* 8MB, 64bit शेष */
		पूर्ण
#अगर !defined(__i386__) && !defined(__x86_64__)
	पूर्ण
#पूर्ण_अगर
	अगर(bios) अणु
		v1 = bios[0xe6];
		v2 = bios[0xe7];
	पूर्ण अन्यथा अणु
		reg = SiS_GetReg(SISSR, 0x3a);
		अगर((reg & 0x30) == 0x30) अणु
			v1 = 0x04; /* PCI */
			v2 = 0x92;
		पूर्ण अन्यथा अणु
			v1 = 0x14; /* AGP */
			v2 = 0xb2;
		पूर्ण
	पूर्ण
	SiS_SetReg(SISSR, 0x21, v1);
	SiS_SetReg(SISSR, 0x22, v2);

	/* Sense CRT1 */
	sisfb_sense_crt1(ivideo);

	/* Set शेष mode, करोn't clear screen */
	ivideo->SiS_Pr.SiS_UseOEM = false;
	SiS_SetEnableDstn(&ivideo->SiS_Pr, false);
	SiS_SetEnableFstn(&ivideo->SiS_Pr, false);
	ivideo->curFSTN = ivideo->curDSTN = 0;
	ivideo->SiS_Pr.VideoMemorySize = 8 << 20;
	SiSSetMode(&ivideo->SiS_Pr, 0x2e | 0x80);

	SiS_SetReg(SISSR, 0x05, 0x86);

	/* Display off */
	SiS_SetRegOR(SISSR, 0x01, 0x20);

	/* Save mode number in CR34 */
	SiS_SetReg(SISCR, 0x34, 0x2e);

	/* Let everyone know what the current mode is */
	ivideo->modeprechange = 0x2e;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
#अगर 0
अटल व्योम sisfb_post_sis315330(काष्ठा pci_dev *pdev)
अणु
	/* TODO */
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक sisfb_xgi_is21(काष्ठा sis_video_info *ivideo)
अणु
	वापस ivideo->chip_real_id == XGI_21;
पूर्ण

अटल व्योम sisfb_post_xgi_delay(काष्ठा sis_video_info *ivideo, पूर्णांक delay)
अणु
	अचिन्हित पूर्णांक i;
	u8 reg;

	क्रम(i = 0; i <= (delay * 10 * 36); i++) अणु
		reg = SiS_GetReg(SISSR, 0x05);
		reg++;
	पूर्ण
पूर्ण

अटल पूर्णांक sisfb_find_host_bridge(काष्ठा sis_video_info *ivideo,
				  काष्ठा pci_dev *mypdev,
				  अचिन्हित लघु pcivenकरोr)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	अचिन्हित लघु temp;
	पूर्णांक ret = 0;

	जबतक((pdev = pci_get_class(PCI_CLASS_BRIDGE_HOST, pdev))) अणु
		temp = pdev->venकरोr;
		अगर(temp == pcivenकरोr) अणु
			ret = 1;
			pci_dev_put(pdev);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sisfb_post_xgi_rwtest(काष्ठा sis_video_info *ivideo, पूर्णांक starta,
				 अचिन्हित पूर्णांक enda, अचिन्हित पूर्णांक mapsize)
अणु
	अचिन्हित पूर्णांक pos;
	पूर्णांक i;

	ग_लिखोl(0, ivideo->video_vbase);

	क्रम(i = starta; i <= enda; i++) अणु
		pos = 1 << i;
		अगर(pos < mapsize)
			ग_लिखोl(pos, ivideo->video_vbase + pos);
	पूर्ण

	sisfb_post_xgi_delay(ivideo, 150);

	अगर(पढ़ोl(ivideo->video_vbase) != 0)
		वापस 0;

	क्रम(i = starta; i <= enda; i++) अणु
		pos = 1 << i;
		अगर(pos < mapsize) अणु
			अगर(पढ़ोl(ivideo->video_vbase + pos) != pos)
				वापस 0;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक sisfb_post_xgi_ramsize(काष्ठा sis_video_info *ivideo)
अणु
	अचिन्हित पूर्णांक buswidth, ranksize, channelab, mapsize;
	पूर्णांक i, j, k, l, status;
	u8 reg, sr14;
	अटल स्थिर u8 dramsr13[12 * 5] = अणु
		0x02, 0x0e, 0x0b, 0x80, 0x5d,
		0x02, 0x0e, 0x0a, 0x40, 0x59,
		0x02, 0x0d, 0x0b, 0x40, 0x4d,
		0x02, 0x0e, 0x09, 0x20, 0x55,
		0x02, 0x0d, 0x0a, 0x20, 0x49,
		0x02, 0x0c, 0x0b, 0x20, 0x3d,
		0x02, 0x0e, 0x08, 0x10, 0x51,
		0x02, 0x0d, 0x09, 0x10, 0x45,
		0x02, 0x0c, 0x0a, 0x10, 0x39,
		0x02, 0x0d, 0x08, 0x08, 0x41,
		0x02, 0x0c, 0x09, 0x08, 0x35,
		0x02, 0x0c, 0x08, 0x04, 0x31
	पूर्ण;
	अटल स्थिर u8 dramsr13_4[4 * 5] = अणु
		0x02, 0x0d, 0x09, 0x40, 0x45,
		0x02, 0x0c, 0x09, 0x20, 0x35,
		0x02, 0x0c, 0x08, 0x10, 0x31,
		0x02, 0x0b, 0x08, 0x08, 0x21
	पूर्ण;

	/* Enable linear mode, disable 0xa0000 address decoding */
	/* We disable a0000 address decoding, because
	 * - अगर running on x86, अगर the card is disabled, it means
	 *   that another card is in the प्रणाली. We करोn't want
	 *   to पूर्णांकerphere with that primary card's texपंचांगode.
	 * - अगर running on non-x86, there usually is no VGA winकरोw
	 *   at a0000.
	 */
	SiS_SetRegOR(SISSR, 0x20, (0x80 | 0x04));

	/* Need to map max FB size क्रम finding out about RAM size */
	mapsize = ivideo->video_size;
	sisfb_post_map_vram(ivideo, &mapsize, 32);

	अगर(!ivideo->video_vbase) अणु
		prपूर्णांकk(KERN_ERR "sisfb: Unable to detect RAM size. Setting default.\n");
		SiS_SetReg(SISSR, 0x13, 0x35);
		SiS_SetReg(SISSR, 0x14, 0x41);
		/* TODO */
		वापस -ENOMEM;
	पूर्ण

	/* Non-पूर्णांकerleaving */
	SiS_SetReg(SISSR, 0x15, 0x00);
	/* No tiling */
	SiS_SetReg(SISSR, 0x1c, 0x00);

	अगर(ivideo->chip == XGI_20) अणु

		channelab = 1;
		reg = SiS_GetReg(SISCR, 0x97);
		अगर(!(reg & 0x01)) अणु	/* Single 32/16 */
			buswidth = 32;
			SiS_SetReg(SISSR, 0x13, 0xb1);
			SiS_SetReg(SISSR, 0x14, 0x52);
			sisfb_post_xgi_delay(ivideo, 1);
			sr14 = 0x02;
			अगर(sisfb_post_xgi_rwtest(ivideo, 23, 24, mapsize))
				जाओ bail_out;

			SiS_SetReg(SISSR, 0x13, 0x31);
			SiS_SetReg(SISSR, 0x14, 0x42);
			sisfb_post_xgi_delay(ivideo, 1);
			अगर(sisfb_post_xgi_rwtest(ivideo, 23, 23, mapsize))
				जाओ bail_out;

			buswidth = 16;
			SiS_SetReg(SISSR, 0x13, 0xb1);
			SiS_SetReg(SISSR, 0x14, 0x41);
			sisfb_post_xgi_delay(ivideo, 1);
			sr14 = 0x01;
			अगर(sisfb_post_xgi_rwtest(ivideo, 22, 23, mapsize))
				जाओ bail_out;
			अन्यथा
				SiS_SetReg(SISSR, 0x13, 0x31);
		पूर्ण अन्यथा अणु		/* Dual 16/8 */
			buswidth = 16;
			SiS_SetReg(SISSR, 0x13, 0xb1);
			SiS_SetReg(SISSR, 0x14, 0x41);
			sisfb_post_xgi_delay(ivideo, 1);
			sr14 = 0x01;
			अगर(sisfb_post_xgi_rwtest(ivideo, 22, 23, mapsize))
				जाओ bail_out;

			SiS_SetReg(SISSR, 0x13, 0x31);
			SiS_SetReg(SISSR, 0x14, 0x31);
			sisfb_post_xgi_delay(ivideo, 1);
			अगर(sisfb_post_xgi_rwtest(ivideo, 22, 22, mapsize))
				जाओ bail_out;

			buswidth = 8;
			SiS_SetReg(SISSR, 0x13, 0xb1);
			SiS_SetReg(SISSR, 0x14, 0x30);
			sisfb_post_xgi_delay(ivideo, 1);
			sr14 = 0x00;
			अगर(sisfb_post_xgi_rwtest(ivideo, 21, 22, mapsize))
				जाओ bail_out;
			अन्यथा
				SiS_SetReg(SISSR, 0x13, 0x31);
		पूर्ण

	पूर्ण अन्यथा अणु	/* XGI_40 */

		reg = SiS_GetReg(SISCR, 0x97);
		अगर(!(reg & 0x10)) अणु
			reg = SiS_GetReg(SISSR, 0x39);
			reg >>= 1;
		पूर्ण

		अगर(reg & 0x01) अणु	/* DDRII */
			buswidth = 32;
			अगर(ivideo->revision_id == 2) अणु
				channelab = 2;
				SiS_SetReg(SISSR, 0x13, 0xa1);
				SiS_SetReg(SISSR, 0x14, 0x44);
				sr14 = 0x04;
				sisfb_post_xgi_delay(ivideo, 1);
				अगर(sisfb_post_xgi_rwtest(ivideo, 23, 24, mapsize))
					जाओ bail_out;

				SiS_SetReg(SISSR, 0x13, 0x21);
				SiS_SetReg(SISSR, 0x14, 0x34);
				अगर(sisfb_post_xgi_rwtest(ivideo, 22, 23, mapsize))
					जाओ bail_out;

				channelab = 1;
				SiS_SetReg(SISSR, 0x13, 0xa1);
				SiS_SetReg(SISSR, 0x14, 0x40);
				sr14 = 0x00;
				अगर(sisfb_post_xgi_rwtest(ivideo, 22, 23, mapsize))
					जाओ bail_out;

				SiS_SetReg(SISSR, 0x13, 0x21);
				SiS_SetReg(SISSR, 0x14, 0x30);
			पूर्ण अन्यथा अणु
				channelab = 3;
				SiS_SetReg(SISSR, 0x13, 0xa1);
				SiS_SetReg(SISSR, 0x14, 0x4c);
				sr14 = 0x0c;
				sisfb_post_xgi_delay(ivideo, 1);
				अगर(sisfb_post_xgi_rwtest(ivideo, 23, 25, mapsize))
					जाओ bail_out;

				channelab = 2;
				SiS_SetReg(SISSR, 0x14, 0x48);
				sisfb_post_xgi_delay(ivideo, 1);
				sr14 = 0x08;
				अगर(sisfb_post_xgi_rwtest(ivideo, 23, 24, mapsize))
					जाओ bail_out;

				SiS_SetReg(SISSR, 0x13, 0x21);
				SiS_SetReg(SISSR, 0x14, 0x3c);
				sr14 = 0x0c;

				अगर(sisfb_post_xgi_rwtest(ivideo, 23, 24, mapsize)) अणु
					channelab = 3;
				पूर्ण अन्यथा अणु
					channelab = 2;
					SiS_SetReg(SISSR, 0x14, 0x38);
					sr14 = 0x08;
				पूर्ण
			पूर्ण
			sisfb_post_xgi_delay(ivideo, 1);

		पूर्ण अन्यथा अणु	/* DDR */

			buswidth = 64;
			अगर(ivideo->revision_id == 2) अणु
				channelab = 1;
				SiS_SetReg(SISSR, 0x13, 0xa1);
				SiS_SetReg(SISSR, 0x14, 0x52);
				sisfb_post_xgi_delay(ivideo, 1);
				sr14 = 0x02;
				अगर(sisfb_post_xgi_rwtest(ivideo, 23, 24, mapsize))
					जाओ bail_out;

				SiS_SetReg(SISSR, 0x13, 0x21);
				SiS_SetReg(SISSR, 0x14, 0x42);
			पूर्ण अन्यथा अणु
				channelab = 2;
				SiS_SetReg(SISSR, 0x13, 0xa1);
				SiS_SetReg(SISSR, 0x14, 0x5a);
				sisfb_post_xgi_delay(ivideo, 1);
				sr14 = 0x0a;
				अगर(sisfb_post_xgi_rwtest(ivideo, 24, 25, mapsize))
					जाओ bail_out;

				SiS_SetReg(SISSR, 0x13, 0x21);
				SiS_SetReg(SISSR, 0x14, 0x4a);
			पूर्ण
			sisfb_post_xgi_delay(ivideo, 1);

		पूर्ण
	पूर्ण

bail_out:
	SiS_SetRegANDOR(SISSR, 0x14, 0xf0, sr14);
	sisfb_post_xgi_delay(ivideo, 1);

	j = (ivideo->chip == XGI_20) ? 5 : 9;
	k = (ivideo->chip == XGI_20) ? 12 : 4;
	status = -EIO;

	क्रम(i = 0; i < k; i++) अणु

		reg = (ivideo->chip == XGI_20) ?
				dramsr13[(i * 5) + 4] : dramsr13_4[(i * 5) + 4];
		SiS_SetRegANDOR(SISSR, 0x13, 0x80, reg);
		sisfb_post_xgi_delay(ivideo, 50);

		ranksize = (ivideo->chip == XGI_20) ?
				dramsr13[(i * 5) + 3] : dramsr13_4[(i * 5) + 3];

		reg = SiS_GetReg(SISSR, 0x13);
		अगर(reg & 0x80) ranksize <<= 1;

		अगर(ivideo->chip == XGI_20) अणु
			अगर(buswidth == 16)      ranksize <<= 1;
			अन्यथा अगर(buswidth == 32) ranksize <<= 2;
		पूर्ण अन्यथा अणु
			अगर(buswidth == 64)      ranksize <<= 1;
		पूर्ण

		reg = 0;
		l = channelab;
		अगर(l == 3) l = 4;
		अगर((ranksize * l) <= 256) अणु
			जबतक((ranksize >>= 1)) reg += 0x10;
		पूर्ण

		अगर(!reg) जारी;

		SiS_SetRegANDOR(SISSR, 0x14, 0x0f, (reg & 0xf0));
		sisfb_post_xgi_delay(ivideo, 1);

		अगर (sisfb_post_xgi_rwtest(ivideo, j, ((reg >> 4) + channelab - 2 + 20), mapsize)) अणु
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	iounmap(ivideo->video_vbase);

	वापस status;
पूर्ण

अटल व्योम sisfb_post_xgi_setघड़ीs(काष्ठा sis_video_info *ivideo, u8 regb)
अणु
	u8 v1, v2, v3;
	पूर्णांक index;
	अटल स्थिर u8 cs90[8 * 3] = अणु
		0x16, 0x01, 0x01,
		0x3e, 0x03, 0x01,
		0x7c, 0x08, 0x01,
		0x79, 0x06, 0x01,
		0x29, 0x01, 0x81,
		0x5c, 0x23, 0x01,
		0x5c, 0x23, 0x01,
		0x5c, 0x23, 0x01
	पूर्ण;
	अटल स्थिर u8 csb8[8 * 3] = अणु
		0x5c, 0x23, 0x01,
		0x29, 0x01, 0x01,
		0x7c, 0x08, 0x01,
		0x79, 0x06, 0x01,
		0x29, 0x01, 0x81,
		0x5c, 0x23, 0x01,
		0x5c, 0x23, 0x01,
		0x5c, 0x23, 0x01
	पूर्ण;

	regb = 0;  /* ! */

	index = regb * 3;
	v1 = cs90[index]; v2 = cs90[index + 1]; v3 = cs90[index + 2];
	अगर(ivideo->haveXGIROM) अणु
		v1 = ivideo->bios_abase[0x90 + index];
		v2 = ivideo->bios_abase[0x90 + index + 1];
		v3 = ivideo->bios_abase[0x90 + index + 2];
	पूर्ण
	SiS_SetReg(SISSR, 0x28, v1);
	SiS_SetReg(SISSR, 0x29, v2);
	SiS_SetReg(SISSR, 0x2a, v3);
	sisfb_post_xgi_delay(ivideo, 0x43);
	sisfb_post_xgi_delay(ivideo, 0x43);
	sisfb_post_xgi_delay(ivideo, 0x43);
	index = regb * 3;
	v1 = csb8[index]; v2 = csb8[index + 1]; v3 = csb8[index + 2];
	अगर(ivideo->haveXGIROM) अणु
		v1 = ivideo->bios_abase[0xb8 + index];
		v2 = ivideo->bios_abase[0xb8 + index + 1];
		v3 = ivideo->bios_abase[0xb8 + index + 2];
	पूर्ण
	SiS_SetReg(SISSR, 0x2e, v1);
	SiS_SetReg(SISSR, 0x2f, v2);
	SiS_SetReg(SISSR, 0x30, v3);
	sisfb_post_xgi_delay(ivideo, 0x43);
	sisfb_post_xgi_delay(ivideo, 0x43);
	sisfb_post_xgi_delay(ivideo, 0x43);
पूर्ण

अटल व्योम sisfb_post_xgi_ddr2_mrs_शेष(काष्ठा sis_video_info *ivideo,
					    u8 regb)
अणु
	अचिन्हित अक्षर *bios = ivideo->bios_abase;
	u8 v1;

	SiS_SetReg(SISSR, 0x28, 0x64);
	SiS_SetReg(SISSR, 0x29, 0x63);
	sisfb_post_xgi_delay(ivideo, 15);
	SiS_SetReg(SISSR, 0x18, 0x00);
	SiS_SetReg(SISSR, 0x19, 0x20);
	SiS_SetReg(SISSR, 0x16, 0x00);
	SiS_SetReg(SISSR, 0x16, 0x80);
	SiS_SetReg(SISSR, 0x18, 0xc5);
	SiS_SetReg(SISSR, 0x19, 0x23);
	SiS_SetReg(SISSR, 0x16, 0x00);
	SiS_SetReg(SISSR, 0x16, 0x80);
	sisfb_post_xgi_delay(ivideo, 1);
	SiS_SetReg(SISCR, 0x97, 0x11);
	sisfb_post_xgi_setघड़ीs(ivideo, regb);
	sisfb_post_xgi_delay(ivideo, 0x46);
	SiS_SetReg(SISSR, 0x18, 0xc5);
	SiS_SetReg(SISSR, 0x19, 0x23);
	SiS_SetReg(SISSR, 0x16, 0x00);
	SiS_SetReg(SISSR, 0x16, 0x80);
	sisfb_post_xgi_delay(ivideo, 1);
	SiS_SetReg(SISSR, 0x1b, 0x04);
	sisfb_post_xgi_delay(ivideo, 1);
	SiS_SetReg(SISSR, 0x1b, 0x00);
	sisfb_post_xgi_delay(ivideo, 1);
	v1 = 0x31;
	अगर (ivideo->haveXGIROM) अणु
		v1 = bios[0xf0];
	पूर्ण
	SiS_SetReg(SISSR, 0x18, v1);
	SiS_SetReg(SISSR, 0x19, 0x06);
	SiS_SetReg(SISSR, 0x16, 0x04);
	SiS_SetReg(SISSR, 0x16, 0x84);
	sisfb_post_xgi_delay(ivideo, 1);
पूर्ण

अटल व्योम sisfb_post_xgi_ddr2_mrs_xg21(काष्ठा sis_video_info *ivideo)
अणु
	sisfb_post_xgi_setघड़ीs(ivideo, 1);

	SiS_SetReg(SISCR, 0x97, 0x11);
	sisfb_post_xgi_delay(ivideo, 0x46);

	SiS_SetReg(SISSR, 0x18, 0x00);	/* EMRS2 */
	SiS_SetReg(SISSR, 0x19, 0x80);
	SiS_SetReg(SISSR, 0x16, 0x05);
	SiS_SetReg(SISSR, 0x16, 0x85);

	SiS_SetReg(SISSR, 0x18, 0x00);	/* EMRS3 */
	SiS_SetReg(SISSR, 0x19, 0xc0);
	SiS_SetReg(SISSR, 0x16, 0x05);
	SiS_SetReg(SISSR, 0x16, 0x85);

	SiS_SetReg(SISSR, 0x18, 0x00);	/* EMRS1 */
	SiS_SetReg(SISSR, 0x19, 0x40);
	SiS_SetReg(SISSR, 0x16, 0x05);
	SiS_SetReg(SISSR, 0x16, 0x85);

	SiS_SetReg(SISSR, 0x18, 0x42);	/* MRS1 */
	SiS_SetReg(SISSR, 0x19, 0x02);
	SiS_SetReg(SISSR, 0x16, 0x05);
	SiS_SetReg(SISSR, 0x16, 0x85);
	sisfb_post_xgi_delay(ivideo, 1);

	SiS_SetReg(SISSR, 0x1b, 0x04);
	sisfb_post_xgi_delay(ivideo, 1);

	SiS_SetReg(SISSR, 0x1b, 0x00);
	sisfb_post_xgi_delay(ivideo, 1);

	SiS_SetReg(SISSR, 0x18, 0x42);	/* MRS1 */
	SiS_SetReg(SISSR, 0x19, 0x00);
	SiS_SetReg(SISSR, 0x16, 0x05);
	SiS_SetReg(SISSR, 0x16, 0x85);
	sisfb_post_xgi_delay(ivideo, 1);
पूर्ण

अटल व्योम sisfb_post_xgi_ddr2(काष्ठा sis_video_info *ivideo, u8 regb)
अणु
	अचिन्हित अक्षर *bios = ivideo->bios_abase;
	अटल स्थिर u8 cs158[8] = अणु
		0x88, 0xaa, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs160[8] = अणु
		0x44, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs168[8] = अणु
		0x48, 0x78, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	u8 v1;
	u8 v2;
	u8 v3;

	SiS_SetReg(SISCR, 0xb0, 0x80); /* DDR2 dual frequency mode */
	SiS_SetReg(SISCR, 0x82, 0x77);
	SiS_SetReg(SISCR, 0x86, 0x00);
	SiS_GetReg(SISCR, 0x86);
	SiS_SetReg(SISCR, 0x86, 0x88);
	SiS_GetReg(SISCR, 0x86);
	v1 = cs168[regb]; v2 = cs160[regb]; v3 = cs158[regb];
	अगर (ivideo->haveXGIROM) अणु
		v1 = bios[regb + 0x168];
		v2 = bios[regb + 0x160];
		v3 = bios[regb + 0x158];
	पूर्ण
	SiS_SetReg(SISCR, 0x86, v1);
	SiS_SetReg(SISCR, 0x82, 0x77);
	SiS_SetReg(SISCR, 0x85, 0x00);
	SiS_GetReg(SISCR, 0x85);
	SiS_SetReg(SISCR, 0x85, 0x88);
	SiS_GetReg(SISCR, 0x85);
	SiS_SetReg(SISCR, 0x85, v2);
	SiS_SetReg(SISCR, 0x82, v3);
	SiS_SetReg(SISCR, 0x98, 0x01);
	SiS_SetReg(SISCR, 0x9a, 0x02);
	अगर (sisfb_xgi_is21(ivideo))
		sisfb_post_xgi_ddr2_mrs_xg21(ivideo);
	अन्यथा
		sisfb_post_xgi_ddr2_mrs_शेष(ivideo, regb);
पूर्ण

अटल u8 sisfb_post_xgi_ramtype(काष्ठा sis_video_info *ivideo)
अणु
	अचिन्हित अक्षर *bios = ivideo->bios_abase;
	u8 ramtype;
	u8 reg;
	u8 v1;

	ramtype = 0x00; v1 = 0x10;
	अगर (ivideo->haveXGIROM) अणु
		ramtype = bios[0x62];
		v1 = bios[0x1d2];
	पूर्ण
	अगर (!(ramtype & 0x80)) अणु
		अगर (sisfb_xgi_is21(ivideo)) अणु
			SiS_SetRegAND(SISCR, 0xb4, 0xfd); /* GPIO control */
			SiS_SetRegOR(SISCR, 0x4a, 0x80);  /* GPIOH EN */
			reg = SiS_GetReg(SISCR, 0x48);
			SiS_SetRegOR(SISCR, 0xb4, 0x02);
			ramtype = reg & 0x01;		  /* GPIOH */
		पूर्ण अन्यथा अगर (ivideo->chip == XGI_20) अणु
			SiS_SetReg(SISCR, 0x97, v1);
			reg = SiS_GetReg(SISCR, 0x97);
			अगर (reg & 0x10) अणु
				ramtype = (reg & 0x01) << 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			reg = SiS_GetReg(SISSR, 0x39);
			ramtype = reg & 0x02;
			अगर (!(ramtype)) अणु
				reg = SiS_GetReg(SISSR, 0x3a);
				ramtype = (reg >> 1) & 0x01;
			पूर्ण
		पूर्ण
	पूर्ण
	ramtype &= 0x07;

	वापस ramtype;
पूर्ण

अटल पूर्णांक sisfb_post_xgi(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sis_video_info *ivideo = pci_get_drvdata(pdev);
	अचिन्हित अक्षर *bios = ivideo->bios_abase;
	काष्ठा pci_dev *mypdev = शून्य;
	स्थिर u8 *ptr, *ptr2;
	u8 v1, v2, v3, v4, v5, reg, ramtype;
	u32 rega, regb, regd;
	पूर्णांक i, j, k, index;
	अटल स्थिर u8 cs78[3] = अणु 0xf6, 0x0d, 0x00 पूर्ण;
	अटल स्थिर u8 cs76[2] = अणु 0xa3, 0xfb पूर्ण;
	अटल स्थिर u8 cs7b[3] = अणु 0xc0, 0x11, 0x00 पूर्ण;
	अटल स्थिर u8 cs158[8] = अणु
		0x88, 0xaa, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs160[8] = अणु
		0x44, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs168[8] = अणु
		0x48, 0x78, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs128[3 * 8] = अणु
		0x90, 0x28, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x77, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x77, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs148[2 * 8] = अणु
		0x55, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs31a[8 * 4] = अणु
		0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
		0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs33a[8 * 4] = अणु
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs45a[8 * 2] = अणु
		0x00, 0x00, 0xa0, 0x00, 0xa0, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs170[7 * 8] = अणु
		0x54, 0x32, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x54, 0x43, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x0a, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x44, 0x34, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x10, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x11, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs1a8[3 * 8] = अणु
		0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x05, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cs100[2 * 8] = अणु
		0xc4, 0x04, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xc4, 0x04, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;

	/* VGA enable */
	reg = SiS_GetRegByte(SISVGAENABLE) | 0x01;
	SiS_SetRegByte(SISVGAENABLE, reg);

	/* Misc */
	reg = SiS_GetRegByte(SISMISCR) | 0x01;
	SiS_SetRegByte(SISMISCW, reg);

	/* Unlock SR */
	SiS_SetReg(SISSR, 0x05, 0x86);
	reg = SiS_GetReg(SISSR, 0x05);
	अगर(reg != 0xa1)
		वापस 0;

	/* Clear some regs */
	क्रम(i = 0; i < 0x22; i++) अणु
		अगर(0x06 + i == 0x20) जारी;
		SiS_SetReg(SISSR, 0x06 + i, 0x00);
	पूर्ण
	क्रम(i = 0; i < 0x0b; i++) अणु
		SiS_SetReg(SISSR, 0x31 + i, 0x00);
	पूर्ण
	क्रम(i = 0; i < 0x10; i++) अणु
		SiS_SetReg(SISCR, 0x30 + i, 0x00);
	पूर्ण

	ptr = cs78;
	अगर(ivideo->haveXGIROM) अणु
		ptr = (स्थिर u8 *)&bios[0x78];
	पूर्ण
	क्रम(i = 0; i < 3; i++) अणु
		SiS_SetReg(SISSR, 0x23 + i, ptr[i]);
	पूर्ण

	ptr = cs76;
	अगर(ivideo->haveXGIROM) अणु
		ptr = (स्थिर u8 *)&bios[0x76];
	पूर्ण
	क्रम(i = 0; i < 2; i++) अणु
		SiS_SetReg(SISSR, 0x21 + i, ptr[i]);
	पूर्ण

	v1 = 0x18; v2 = 0x00;
	अगर(ivideo->haveXGIROM) अणु
		v1 = bios[0x74];
		v2 = bios[0x75];
	पूर्ण
	SiS_SetReg(SISSR, 0x07, v1);
	SiS_SetReg(SISSR, 0x11, 0x0f);
	SiS_SetReg(SISSR, 0x1f, v2);
	/* PCI linear mode, RelIO enabled, A0000 decoding disabled */
	SiS_SetReg(SISSR, 0x20, 0x80 | 0x20 | 0x04);
	SiS_SetReg(SISSR, 0x27, 0x74);

	ptr = cs7b;
	अगर(ivideo->haveXGIROM) अणु
		ptr = (स्थिर u8 *)&bios[0x7b];
	पूर्ण
	क्रम(i = 0; i < 3; i++) अणु
		SiS_SetReg(SISSR, 0x31 + i, ptr[i]);
	पूर्ण

	अगर(ivideo->chip == XGI_40) अणु
		अगर(ivideo->revision_id == 2) अणु
			SiS_SetRegANDOR(SISSR, 0x3b, 0x3f, 0xc0);
		पूर्ण
		SiS_SetReg(SISCR, 0x7d, 0xfe);
		SiS_SetReg(SISCR, 0x7e, 0x0f);
	पूर्ण
	अगर(ivideo->revision_id == 0) अणु	/* 40 *and* 20? */
		SiS_SetRegAND(SISCR, 0x58, 0xd7);
		reg = SiS_GetReg(SISCR, 0xcb);
		अगर(reg & 0x20) अणु
			SiS_SetRegANDOR(SISCR, 0x58, 0xd7, (reg & 0x10) ? 0x08 : 0x20); /* =0x28 Z7 ? */
		पूर्ण
	पूर्ण

	reg = (ivideo->chip == XGI_40) ? 0x20 : 0x00;
	SiS_SetRegANDOR(SISCR, 0x38, 0x1f, reg);

	अगर(ivideo->chip == XGI_20) अणु
		SiS_SetReg(SISSR, 0x36, 0x70);
	पूर्ण अन्यथा अणु
		SiS_SetReg(SISVID, 0x00, 0x86);
		SiS_SetReg(SISVID, 0x32, 0x00);
		SiS_SetReg(SISVID, 0x30, 0x00);
		SiS_SetReg(SISVID, 0x32, 0x01);
		SiS_SetReg(SISVID, 0x30, 0x00);
		SiS_SetRegAND(SISVID, 0x2f, 0xdf);
		SiS_SetRegAND(SISCAP, 0x00, 0x3f);

		SiS_SetReg(SISPART1, 0x2f, 0x01);
		SiS_SetReg(SISPART1, 0x00, 0x00);
		SiS_SetReg(SISPART1, 0x02, bios[0x7e]);
		SiS_SetReg(SISPART1, 0x2e, 0x08);
		SiS_SetRegAND(SISPART1, 0x35, 0x7f);
		SiS_SetRegAND(SISPART1, 0x50, 0xfe);

		reg = SiS_GetReg(SISPART4, 0x00);
		अगर(reg == 1 || reg == 2) अणु
			SiS_SetReg(SISPART2, 0x00, 0x1c);
			SiS_SetReg(SISPART4, 0x0d, bios[0x7f]);
			SiS_SetReg(SISPART4, 0x0e, bios[0x80]);
			SiS_SetReg(SISPART4, 0x10, bios[0x81]);
			SiS_SetRegAND(SISPART4, 0x0f, 0x3f);

			reg = SiS_GetReg(SISPART4, 0x01);
			अगर((reg & 0xf0) >= 0xb0) अणु
				reg = SiS_GetReg(SISPART4, 0x23);
				अगर(reg & 0x20) reg |= 0x40;
				SiS_SetReg(SISPART4, 0x23, reg);
				reg = (reg & 0x20) ? 0x02 : 0x00;
				SiS_SetRegANDOR(SISPART1, 0x1e, 0xfd, reg);
			पूर्ण
		पूर्ण

		v1 = bios[0x77];

		reg = SiS_GetReg(SISSR, 0x3b);
		अगर(reg & 0x02) अणु
			reg = SiS_GetReg(SISSR, 0x3a);
			v2 = (reg & 0x30) >> 3;
			अगर(!(v2 & 0x04)) v2 ^= 0x02;
			reg = SiS_GetReg(SISSR, 0x39);
			अगर(reg & 0x80) v2 |= 0x80;
			v2 |= 0x01;

			अगर((mypdev = pci_get_device(PCI_VENDOR_ID_SI, 0x0730, शून्य))) अणु
				pci_dev_put(mypdev);
				अगर(((v2 & 0x06) == 2) || ((v2 & 0x06) == 4))
					v2 &= 0xf9;
				v2 |= 0x08;
				v1 &= 0xfe;
			पूर्ण अन्यथा अणु
				mypdev = pci_get_device(PCI_VENDOR_ID_SI, 0x0735, शून्य);
				अगर(!mypdev)
					mypdev = pci_get_device(PCI_VENDOR_ID_SI, 0x0645, शून्य);
				अगर(!mypdev)
					mypdev = pci_get_device(PCI_VENDOR_ID_SI, 0x0650, शून्य);
				अगर(mypdev) अणु
					pci_पढ़ो_config_dword(mypdev, 0x94, &regd);
					regd &= 0xfffffeff;
					pci_ग_लिखो_config_dword(mypdev, 0x94, regd);
					v1 &= 0xfe;
					pci_dev_put(mypdev);
				पूर्ण अन्यथा अगर(sisfb_find_host_bridge(ivideo, pdev, PCI_VENDOR_ID_SI)) अणु
					v1 &= 0xfe;
				पूर्ण अन्यथा अगर(sisfb_find_host_bridge(ivideo, pdev, 0x1106) ||
					  sisfb_find_host_bridge(ivideo, pdev, 0x1022) ||
					  sisfb_find_host_bridge(ivideo, pdev, 0x700e) ||
					  sisfb_find_host_bridge(ivideo, pdev, 0x10de)) अणु
					अगर((v2 & 0x06) == 4)
						v2 ^= 0x06;
					v2 |= 0x08;
				पूर्ण
			पूर्ण
			SiS_SetRegANDOR(SISCR, 0x5f, 0xf0, v2);
		पूर्ण
		SiS_SetReg(SISSR, 0x22, v1);

		अगर(ivideo->revision_id == 2) अणु
			v1 = SiS_GetReg(SISSR, 0x3b);
			v2 = SiS_GetReg(SISSR, 0x3a);
			regd = bios[0x90 + 3] | (bios[0x90 + 4] << 8);
			अगर( (!(v1 & 0x02)) && (v2 & 0x30) && (regd < 0xcf) )
				SiS_SetRegANDOR(SISCR, 0x5f, 0xf1, 0x01);

			अगर((mypdev = pci_get_device(0x10de, 0x01e0, शून्य))) अणु
				/* TODO: set CR5f &0xf1 | 0x01 क्रम version 6570
				 * of nक्रमce 2 ROM
				 */
				अगर(0)
					SiS_SetRegANDOR(SISCR, 0x5f, 0xf1, 0x01);
				pci_dev_put(mypdev);
			पूर्ण
		पूर्ण

		v1 = 0x30;
		reg = SiS_GetReg(SISSR, 0x3b);
		v2 = SiS_GetReg(SISCR, 0x5f);
		अगर((!(reg & 0x02)) && (v2 & 0x0e))
			v1 |= 0x08;
		SiS_SetReg(SISSR, 0x27, v1);

		अगर(bios[0x64] & 0x01) अणु
			SiS_SetRegANDOR(SISCR, 0x5f, 0xf0, bios[0x64]);
		पूर्ण

		v1 = bios[0x4f7];
		pci_पढ़ो_config_dword(pdev, 0x50, &regd);
		regd = (regd >> 20) & 0x0f;
		अगर(regd == 1) अणु
			v1 &= 0xfc;
			SiS_SetRegOR(SISCR, 0x5f, 0x08);
		पूर्ण
		SiS_SetReg(SISCR, 0x48, v1);

		SiS_SetRegANDOR(SISCR, 0x47, 0x04, bios[0x4f6] & 0xfb);
		SiS_SetRegANDOR(SISCR, 0x49, 0xf0, bios[0x4f8] & 0x0f);
		SiS_SetRegANDOR(SISCR, 0x4a, 0x60, bios[0x4f9] & 0x9f);
		SiS_SetRegANDOR(SISCR, 0x4b, 0x08, bios[0x4fa] & 0xf7);
		SiS_SetRegANDOR(SISCR, 0x4c, 0x80, bios[0x4fb] & 0x7f);
		SiS_SetReg(SISCR, 0x70, bios[0x4fc]);
		SiS_SetRegANDOR(SISCR, 0x71, 0xf0, bios[0x4fd] & 0x0f);
		SiS_SetReg(SISCR, 0x74, 0xd0);
		SiS_SetRegANDOR(SISCR, 0x74, 0xcf, bios[0x4fe] & 0x30);
		SiS_SetRegANDOR(SISCR, 0x75, 0xe0, bios[0x4ff] & 0x1f);
		SiS_SetRegANDOR(SISCR, 0x76, 0xe0, bios[0x500] & 0x1f);
		v1 = bios[0x501];
		अगर((mypdev = pci_get_device(0x8086, 0x2530, शून्य))) अणु
			v1 = 0xf0;
			pci_dev_put(mypdev);
		पूर्ण
		SiS_SetReg(SISCR, 0x77, v1);
	पूर्ण

	/* RAM type:
	 *
	 * 0 == DDR1, 1 == DDR2, 2..7 == reserved?
	 *
	 * The code seems to written so that regb should equal ramtype,
	 * however, so far it has been hardcoded to 0. Enable other values only
	 * on XGI Z9, as it passes the POST, and add a warning क्रम others.
	 */
	ramtype = sisfb_post_xgi_ramtype(ivideo);
	अगर (!sisfb_xgi_is21(ivideo) && ramtype) अणु
		dev_warn(&pdev->dev,
			 "RAM type something else than expected: %d\n",
			 ramtype);
		regb = 0;
	पूर्ण अन्यथा अणु
		regb = ramtype;
	पूर्ण

	v1 = 0xff;
	अगर(ivideo->haveXGIROM) अणु
		v1 = bios[0x140 + regb];
	पूर्ण
	SiS_SetReg(SISCR, 0x6d, v1);

	ptr = cs128;
	अगर(ivideo->haveXGIROM) अणु
		ptr = (स्थिर u8 *)&bios[0x128];
	पूर्ण
	क्रम(i = 0, j = 0; i < 3; i++, j += 8) अणु
		SiS_SetReg(SISCR, 0x68 + i, ptr[j + regb]);
	पूर्ण

	ptr  = cs31a;
	ptr2 = cs33a;
	अगर(ivideo->haveXGIROM) अणु
		index = (ivideo->chip == XGI_20) ? 0x31a : 0x3a6;
		ptr  = (स्थिर u8 *)&bios[index];
		ptr2 = (स्थिर u8 *)&bios[index + 0x20];
	पूर्ण
	क्रम(i = 0; i < 2; i++) अणु
		अगर(i == 0) अणु
			regd = le32_to_cpu(((u32 *)ptr)[regb]);
			rega = 0x6b;
		पूर्ण अन्यथा अणु
			regd = le32_to_cpu(((u32 *)ptr2)[regb]);
			rega = 0x6e;
		पूर्ण
		reg = 0x00;
		क्रम(j = 0; j < 16; j++) अणु
			reg &= 0xf3;
			अगर(regd & 0x01) reg |= 0x04;
			अगर(regd & 0x02) reg |= 0x08;
			regd >>= 2;
			SiS_SetReg(SISCR, rega, reg);
			reg = SiS_GetReg(SISCR, rega);
			reg = SiS_GetReg(SISCR, rega);
			reg += 0x10;
		पूर्ण
	पूर्ण

	SiS_SetRegAND(SISCR, 0x6e, 0xfc);

	ptr  = शून्य;
	अगर(ivideo->haveXGIROM) अणु
		index = (ivideo->chip == XGI_20) ? 0x35a : 0x3e6;
		ptr  = (स्थिर u8 *)&bios[index];
	पूर्ण
	क्रम(i = 0; i < 4; i++) अणु
		SiS_SetRegANDOR(SISCR, 0x6e, 0xfc, i);
		reg = 0x00;
		क्रम(j = 0; j < 2; j++) अणु
			regd = 0;
			अगर(ptr) अणु
				regd = le32_to_cpu(((u32 *)ptr)[regb * 8]);
				ptr += 4;
			पूर्ण
			/* reg = 0x00; */
			क्रम(k = 0; k < 16; k++) अणु
				reg &= 0xfc;
				अगर(regd & 0x01) reg |= 0x01;
				अगर(regd & 0x02) reg |= 0x02;
				regd >>= 2;
				SiS_SetReg(SISCR, 0x6f, reg);
				reg = SiS_GetReg(SISCR, 0x6f);
				reg = SiS_GetReg(SISCR, 0x6f);
				reg += 0x08;
			पूर्ण
		पूर्ण
	पूर्ण

	ptr  = cs148;
	अगर(ivideo->haveXGIROM) अणु
		ptr  = (स्थिर u8 *)&bios[0x148];
	पूर्ण
	क्रम(i = 0, j = 0; i < 2; i++, j += 8) अणु
		SiS_SetReg(SISCR, 0x80 + i, ptr[j + regb]);
	पूर्ण

	SiS_SetRegAND(SISCR, 0x89, 0x8f);

	ptr  = cs45a;
	अगर(ivideo->haveXGIROM) अणु
		index = (ivideo->chip == XGI_20) ? 0x45a : 0x4e6;
		ptr  = (स्थिर u8 *)&bios[index];
	पूर्ण
	regd = le16_to_cpu(((स्थिर u16 *)ptr)[regb]);
	reg = 0x80;
	क्रम(i = 0; i < 5; i++) अणु
		reg &= 0xfc;
		अगर(regd & 0x01) reg |= 0x01;
		अगर(regd & 0x02) reg |= 0x02;
		regd >>= 2;
		SiS_SetReg(SISCR, 0x89, reg);
		reg = SiS_GetReg(SISCR, 0x89);
		reg = SiS_GetReg(SISCR, 0x89);
		reg += 0x10;
	पूर्ण

	v1 = 0xb5; v2 = 0x20; v3 = 0xf0; v4 = 0x13;
	अगर(ivideo->haveXGIROM) अणु
		v1 = bios[0x118 + regb];
		v2 = bios[0xf8 + regb];
		v3 = bios[0x120 + regb];
		v4 = bios[0x1ca];
	पूर्ण
	SiS_SetReg(SISCR, 0x45, v1 & 0x0f);
	SiS_SetReg(SISCR, 0x99, (v1 >> 4) & 0x07);
	SiS_SetRegOR(SISCR, 0x40, v1 & 0x80);
	SiS_SetReg(SISCR, 0x41, v2);

	ptr  = cs170;
	अगर(ivideo->haveXGIROM) अणु
		ptr  = (स्थिर u8 *)&bios[0x170];
	पूर्ण
	क्रम(i = 0, j = 0; i < 7; i++, j += 8) अणु
		SiS_SetReg(SISCR, 0x90 + i, ptr[j + regb]);
	पूर्ण

	SiS_SetReg(SISCR, 0x59, v3);

	ptr  = cs1a8;
	अगर(ivideo->haveXGIROM) अणु
		ptr  = (स्थिर u8 *)&bios[0x1a8];
	पूर्ण
	क्रम(i = 0, j = 0; i < 3; i++, j += 8) अणु
		SiS_SetReg(SISCR, 0xc3 + i, ptr[j + regb]);
	पूर्ण

	ptr  = cs100;
	अगर(ivideo->haveXGIROM) अणु
		ptr  = (स्थिर u8 *)&bios[0x100];
	पूर्ण
	क्रम(i = 0, j = 0; i < 2; i++, j += 8) अणु
		SiS_SetReg(SISCR, 0x8a + i, ptr[j + regb]);
	पूर्ण

	SiS_SetReg(SISCR, 0xcf, v4);

	SiS_SetReg(SISCR, 0x83, 0x09);
	SiS_SetReg(SISCR, 0x87, 0x00);

	अगर(ivideo->chip == XGI_40) अणु
		अगर( (ivideo->revision_id == 1) ||
		    (ivideo->revision_id == 2) ) अणु
			SiS_SetReg(SISCR, 0x8c, 0x87);
		पूर्ण
	पूर्ण

	अगर (regb == 1)
		SiS_SetReg(SISSR, 0x17, 0x80);		/* DDR2 */
	अन्यथा
		SiS_SetReg(SISSR, 0x17, 0x00);		/* DDR1 */
	SiS_SetReg(SISSR, 0x1a, 0x87);

	अगर(ivideo->chip == XGI_20) अणु
		SiS_SetReg(SISSR, 0x15, 0x00);
		SiS_SetReg(SISSR, 0x1c, 0x00);
	पूर्ण

	चयन(ramtype) अणु
	हाल 0:
		sisfb_post_xgi_setघड़ीs(ivideo, regb);
		अगर((ivideo->chip == XGI_20) ||
		   (ivideo->revision_id == 1)   ||
		   (ivideo->revision_id == 2)) अणु
			v1 = cs158[regb]; v2 = cs160[regb]; v3 = cs168[regb];
			अगर(ivideo->haveXGIROM) अणु
				v1 = bios[regb + 0x158];
				v2 = bios[regb + 0x160];
				v3 = bios[regb + 0x168];
			पूर्ण
			SiS_SetReg(SISCR, 0x82, v1);
			SiS_SetReg(SISCR, 0x85, v2);
			SiS_SetReg(SISCR, 0x86, v3);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISCR, 0x82, 0x88);
			SiS_SetReg(SISCR, 0x86, 0x00);
			reg = SiS_GetReg(SISCR, 0x86);
			SiS_SetReg(SISCR, 0x86, 0x88);
			reg = SiS_GetReg(SISCR, 0x86);
			SiS_SetReg(SISCR, 0x86, bios[regb + 0x168]);
			SiS_SetReg(SISCR, 0x82, 0x77);
			SiS_SetReg(SISCR, 0x85, 0x00);
			reg = SiS_GetReg(SISCR, 0x85);
			SiS_SetReg(SISCR, 0x85, 0x88);
			reg = SiS_GetReg(SISCR, 0x85);
			SiS_SetReg(SISCR, 0x85, bios[regb + 0x160]);
			SiS_SetReg(SISCR, 0x82, bios[regb + 0x158]);
		पूर्ण
		अगर(ivideo->chip == XGI_40) अणु
			SiS_SetReg(SISCR, 0x97, 0x00);
		पूर्ण
		SiS_SetReg(SISCR, 0x98, 0x01);
		SiS_SetReg(SISCR, 0x9a, 0x02);

		SiS_SetReg(SISSR, 0x18, 0x01);
		अगर((ivideo->chip == XGI_20) ||
		   (ivideo->revision_id == 2)) अणु
			SiS_SetReg(SISSR, 0x19, 0x40);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISSR, 0x19, 0x20);
		पूर्ण
		SiS_SetReg(SISSR, 0x16, 0x00);
		SiS_SetReg(SISSR, 0x16, 0x80);
		अगर((ivideo->chip == XGI_20) || (bios[0x1cb] != 0x0c)) अणु
			sisfb_post_xgi_delay(ivideo, 0x43);
			sisfb_post_xgi_delay(ivideo, 0x43);
			sisfb_post_xgi_delay(ivideo, 0x43);
			SiS_SetReg(SISSR, 0x18, 0x00);
			अगर((ivideo->chip == XGI_20) ||
			   (ivideo->revision_id == 2)) अणु
				SiS_SetReg(SISSR, 0x19, 0x40);
			पूर्ण अन्यथा अणु
				SiS_SetReg(SISSR, 0x19, 0x20);
			पूर्ण
		पूर्ण अन्यथा अगर((ivideo->chip == XGI_40) && (bios[0x1cb] == 0x0c)) अणु
			/* SiS_SetReg(SISSR, 0x16, 0x0c); */ /* ? */
		पूर्ण
		SiS_SetReg(SISSR, 0x16, 0x00);
		SiS_SetReg(SISSR, 0x16, 0x80);
		sisfb_post_xgi_delay(ivideo, 4);
		v1 = 0x31; v2 = 0x03; v3 = 0x83; v4 = 0x03; v5 = 0x83;
		अगर(ivideo->haveXGIROM) अणु
			v1 = bios[0xf0];
			index = (ivideo->chip == XGI_20) ? 0x4b2 : 0x53e;
			v2 = bios[index];
			v3 = bios[index + 1];
			v4 = bios[index + 2];
			v5 = bios[index + 3];
		पूर्ण
		SiS_SetReg(SISSR, 0x18, v1);
		SiS_SetReg(SISSR, 0x19, ((ivideo->chip == XGI_20) ? 0x02 : 0x01));
		SiS_SetReg(SISSR, 0x16, v2);
		SiS_SetReg(SISSR, 0x16, v3);
		sisfb_post_xgi_delay(ivideo, 0x43);
		SiS_SetReg(SISSR, 0x1b, 0x03);
		sisfb_post_xgi_delay(ivideo, 0x22);
		SiS_SetReg(SISSR, 0x18, v1);
		SiS_SetReg(SISSR, 0x19, 0x00);
		SiS_SetReg(SISSR, 0x16, v4);
		SiS_SetReg(SISSR, 0x16, v5);
		SiS_SetReg(SISSR, 0x1b, 0x00);
		अवरोध;
	हाल 1:
		sisfb_post_xgi_ddr2(ivideo, regb);
		अवरोध;
	शेष:
		sisfb_post_xgi_setघड़ीs(ivideo, regb);
		अगर((ivideo->chip == XGI_40) &&
		   ((ivideo->revision_id == 1) ||
		    (ivideo->revision_id == 2))) अणु
			SiS_SetReg(SISCR, 0x82, bios[regb + 0x158]);
			SiS_SetReg(SISCR, 0x85, bios[regb + 0x160]);
			SiS_SetReg(SISCR, 0x86, bios[regb + 0x168]);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISCR, 0x82, 0x88);
			SiS_SetReg(SISCR, 0x86, 0x00);
			reg = SiS_GetReg(SISCR, 0x86);
			SiS_SetReg(SISCR, 0x86, 0x88);
			SiS_SetReg(SISCR, 0x82, 0x77);
			SiS_SetReg(SISCR, 0x85, 0x00);
			reg = SiS_GetReg(SISCR, 0x85);
			SiS_SetReg(SISCR, 0x85, 0x88);
			reg = SiS_GetReg(SISCR, 0x85);
			v1 = cs160[regb]; v2 = cs158[regb];
			अगर(ivideo->haveXGIROM) अणु
				v1 = bios[regb + 0x160];
				v2 = bios[regb + 0x158];
			पूर्ण
			SiS_SetReg(SISCR, 0x85, v1);
			SiS_SetReg(SISCR, 0x82, v2);
		पूर्ण
		अगर(ivideo->chip == XGI_40) अणु
			SiS_SetReg(SISCR, 0x97, 0x11);
		पूर्ण
		अगर((ivideo->chip == XGI_40) && (ivideo->revision_id == 2)) अणु
			SiS_SetReg(SISCR, 0x98, 0x01);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISCR, 0x98, 0x03);
		पूर्ण
		SiS_SetReg(SISCR, 0x9a, 0x02);

		अगर(ivideo->chip == XGI_40) अणु
			SiS_SetReg(SISSR, 0x18, 0x01);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISSR, 0x18, 0x00);
		पूर्ण
		SiS_SetReg(SISSR, 0x19, 0x40);
		SiS_SetReg(SISSR, 0x16, 0x00);
		SiS_SetReg(SISSR, 0x16, 0x80);
		अगर((ivideo->chip == XGI_40) && (bios[0x1cb] != 0x0c)) अणु
			sisfb_post_xgi_delay(ivideo, 0x43);
			sisfb_post_xgi_delay(ivideo, 0x43);
			sisfb_post_xgi_delay(ivideo, 0x43);
			SiS_SetReg(SISSR, 0x18, 0x00);
			SiS_SetReg(SISSR, 0x19, 0x40);
			SiS_SetReg(SISSR, 0x16, 0x00);
			SiS_SetReg(SISSR, 0x16, 0x80);
		पूर्ण
		sisfb_post_xgi_delay(ivideo, 4);
		v1 = 0x31;
		अगर(ivideo->haveXGIROM) अणु
			v1 = bios[0xf0];
		पूर्ण
		SiS_SetReg(SISSR, 0x18, v1);
		SiS_SetReg(SISSR, 0x19, 0x01);
		अगर(ivideo->chip == XGI_40) अणु
			SiS_SetReg(SISSR, 0x16, bios[0x53e]);
			SiS_SetReg(SISSR, 0x16, bios[0x53f]);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISSR, 0x16, 0x05);
			SiS_SetReg(SISSR, 0x16, 0x85);
		पूर्ण
		sisfb_post_xgi_delay(ivideo, 0x43);
		अगर(ivideo->chip == XGI_40) अणु
			SiS_SetReg(SISSR, 0x1b, 0x01);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISSR, 0x1b, 0x03);
		पूर्ण
		sisfb_post_xgi_delay(ivideo, 0x22);
		SiS_SetReg(SISSR, 0x18, v1);
		SiS_SetReg(SISSR, 0x19, 0x00);
		अगर(ivideo->chip == XGI_40) अणु
			SiS_SetReg(SISSR, 0x16, bios[0x540]);
			SiS_SetReg(SISSR, 0x16, bios[0x541]);
		पूर्ण अन्यथा अणु
			SiS_SetReg(SISSR, 0x16, 0x05);
			SiS_SetReg(SISSR, 0x16, 0x85);
		पूर्ण
		SiS_SetReg(SISSR, 0x1b, 0x00);
	पूर्ण

	regb = 0;	/* ! */
	v1 = 0x03;
	अगर(ivideo->haveXGIROM) अणु
		v1 = bios[0x110 + regb];
	पूर्ण
	SiS_SetReg(SISSR, 0x1b, v1);

	/* RAM size */
	v1 = 0x00; v2 = 0x00;
	अगर(ivideo->haveXGIROM) अणु
		v1 = bios[0x62];
		v2 = bios[0x63];
	पूर्ण
	regb = 0;	/* ! */
	regd = 1 << regb;
	अगर((v1 & 0x40) && (v2 & regd) && ivideo->haveXGIROM) अणु

		SiS_SetReg(SISSR, 0x13, bios[regb + 0xe0]);
		SiS_SetReg(SISSR, 0x14, bios[regb + 0xe0 + 8]);

	पूर्ण अन्यथा अणु
		पूर्णांक err;

		/* Set शेष mode, करोn't clear screen */
		ivideo->SiS_Pr.SiS_UseOEM = false;
		SiS_SetEnableDstn(&ivideo->SiS_Pr, false);
		SiS_SetEnableFstn(&ivideo->SiS_Pr, false);
		ivideo->curFSTN = ivideo->curDSTN = 0;
		ivideo->SiS_Pr.VideoMemorySize = 8 << 20;
		SiSSetMode(&ivideo->SiS_Pr, 0x2e | 0x80);

		SiS_SetReg(SISSR, 0x05, 0x86);

		/* Disable पढ़ो-cache */
		SiS_SetRegAND(SISSR, 0x21, 0xdf);
		err = sisfb_post_xgi_ramsize(ivideo);
		/* Enable पढ़ो-cache */
		SiS_SetRegOR(SISSR, 0x21, 0x20);

		अगर (err) अणु
			dev_err(&pdev->dev,
				"%s: RAM size detection failed: %d\n",
				__func__, err);
			वापस 0;
		पूर्ण
	पूर्ण

#अगर 0
	prपूर्णांकk(KERN_DEBUG "-----------------\n");
	क्रम(i = 0; i < 0xff; i++) अणु
		reg = SiS_GetReg(SISCR, i);
		prपूर्णांकk(KERN_DEBUG "CR%02x(%x) = 0x%02x\n", i, SISCR, reg);
	पूर्ण
	क्रम(i = 0; i < 0x40; i++) अणु
		reg = SiS_GetReg(SISSR, i);
		prपूर्णांकk(KERN_DEBUG "SR%02x(%x) = 0x%02x\n", i, SISSR, reg);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "-----------------\n");
#पूर्ण_अगर

	/* Sense CRT1 */
	अगर(ivideo->chip == XGI_20) अणु
		SiS_SetRegOR(SISCR, 0x32, 0x20);
	पूर्ण अन्यथा अणु
		reg = SiS_GetReg(SISPART4, 0x00);
		अगर((reg == 1) || (reg == 2)) अणु
			sisfb_sense_crt1(ivideo);
		पूर्ण अन्यथा अणु
			SiS_SetRegOR(SISCR, 0x32, 0x20);
		पूर्ण
	पूर्ण

	/* Set शेष mode, करोn't clear screen */
	ivideo->SiS_Pr.SiS_UseOEM = false;
	SiS_SetEnableDstn(&ivideo->SiS_Pr, false);
	SiS_SetEnableFstn(&ivideo->SiS_Pr, false);
	ivideo->curFSTN = ivideo->curDSTN = 0;
	SiSSetMode(&ivideo->SiS_Pr, 0x2e | 0x80);

	SiS_SetReg(SISSR, 0x05, 0x86);

	/* Display off */
	SiS_SetRegOR(SISSR, 0x01, 0x20);

	/* Save mode number in CR34 */
	SiS_SetReg(SISCR, 0x34, 0x2e);

	/* Let everyone know what the current mode is */
	ivideo->modeprechange = 0x2e;

	अगर(ivideo->chip == XGI_40) अणु
		reg = SiS_GetReg(SISCR, 0xca);
		v1 = SiS_GetReg(SISCR, 0xcc);
		अगर((reg & 0x10) && (!(v1 & 0x04))) अणु
			prपूर्णांकk(KERN_ERR
				"sisfb: Please connect power to the card.\n");
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sisfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sisfb_chip_info	*chipinfo = &sisfb_chip_info[ent->driver_data];
	काष्ठा sis_video_info	*ivideo = शून्य;
	काष्ठा fb_info		*sis_fb_info = शून्य;
	u16 reg16;
	u8  reg;
	पूर्णांक i, ret;

	अगर(sisfb_off)
		वापस -ENXIO;

	sis_fb_info = framebuffer_alloc(माप(*ivideo), &pdev->dev);
	अगर(!sis_fb_info)
		वापस -ENOMEM;

	ivideo = (काष्ठा sis_video_info *)sis_fb_info->par;
	ivideo->memyselfandi = sis_fb_info;

	ivideo->sisfb_id = SISFB_ID;

	अगर(card_list == शून्य) अणु
		ivideo->cardnumber = 0;
	पूर्ण अन्यथा अणु
		काष्ठा sis_video_info *countvideo = card_list;
		ivideo->cardnumber = 1;
		जबतक((countvideo = countvideo->next) != शून्य)
			ivideo->cardnumber++;
	पूर्ण

	strlcpy(ivideo->myid, chipinfo->chip_name, माप(ivideo->myid));

	ivideo->warncount = 0;
	ivideo->chip_id = pdev->device;
	ivideo->chip_venकरोr = pdev->venकरोr;
	ivideo->revision_id = pdev->revision;
	ivideo->SiS_Pr.ChipRevision = ivideo->revision_id;
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &reg16);
	ivideo->sisvga_enabled = reg16 & 0x01;
	ivideo->pcibus = pdev->bus->number;
	ivideo->pcislot = PCI_SLOT(pdev->devfn);
	ivideo->pcअगरunc = PCI_FUNC(pdev->devfn);
	ivideo->subsysvenकरोr = pdev->subप्रणाली_venकरोr;
	ivideo->subsysdevice = pdev->subप्रणाली_device;

#अगर_अघोषित MODULE
	अगर(sisfb_mode_idx == -1) अणु
		sisfb_get_vga_mode_from_kernel();
	पूर्ण
#पूर्ण_अगर

	ivideo->chip = chipinfo->chip;
	ivideo->chip_real_id = chipinfo->chip;
	ivideo->sisvga_engine = chipinfo->vgaengine;
	ivideo->hwcursor_size = chipinfo->hwcursor_size;
	ivideo->CRT2_ग_लिखो_enable = chipinfo->CRT2_ग_लिखो_enable;
	ivideo->mni = chipinfo->mni;

	ivideo->detectedpdc  = 0xff;
	ivideo->detectedpdca = 0xff;
	ivideo->detectedlcda = 0xff;

	ivideo->sisfb_thismonitor.datavalid = false;

	ivideo->current_base = 0;

	ivideo->engineok = 0;

	ivideo->sisfb_was_boot_device = 0;

	अगर(pdev->resource[PCI_ROM_RESOURCE].flags & IORESOURCE_ROM_SHADOW) अणु
		अगर(ivideo->sisvga_enabled)
			ivideo->sisfb_was_boot_device = 1;
		अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "sisfb: PCI device is disabled, "
				"but marked as boot video device ???\n");
			prपूर्णांकk(KERN_DEBUG "sisfb: I will not accept this "
				"as the primary VGA device\n");
		पूर्ण
	पूर्ण

	ivideo->sisfb_parm_mem = sisfb_parm_mem;
	ivideo->sisfb_accel = sisfb_accel;
	ivideo->sisfb_ypan = sisfb_ypan;
	ivideo->sisfb_max = sisfb_max;
	ivideo->sisfb_userom = sisfb_userom;
	ivideo->sisfb_useoem = sisfb_useoem;
	ivideo->sisfb_mode_idx = sisfb_mode_idx;
	ivideo->sisfb_parm_rate = sisfb_parm_rate;
	ivideo->sisfb_crt1off = sisfb_crt1off;
	ivideo->sisfb_क्रमcecrt1 = sisfb_क्रमcecrt1;
	ivideo->sisfb_crt2type = sisfb_crt2type;
	ivideo->sisfb_crt2flags = sisfb_crt2flags;
	/* pdc(a), scalelcd, special timing, lvdshl handled below */
	ivideo->sisfb_dstn = sisfb_dstn;
	ivideo->sisfb_fstn = sisfb_fstn;
	ivideo->sisfb_tvplug = sisfb_tvplug;
	ivideo->sisfb_tvstd = sisfb_tvstd;
	ivideo->tvxpos = sisfb_tvxposoffset;
	ivideo->tvypos = sisfb_tvyposoffset;
	ivideo->sisfb_nocrt2rate = sisfb_nocrt2rate;
	ivideo->refresh_rate = 0;
	अगर(ivideo->sisfb_parm_rate != -1) अणु
		ivideo->refresh_rate = ivideo->sisfb_parm_rate;
	पूर्ण

	ivideo->SiS_Pr.UsePanelScaler = sisfb_scalelcd;
	ivideo->SiS_Pr.CenterScreen = -1;
	ivideo->SiS_Pr.SiS_CustomT = sisfb_specialtiming;
	ivideo->SiS_Pr.LVDSHL = sisfb_lvdshl;

	ivideo->SiS_Pr.SiS_Backup70xx = 0xff;
	ivideo->SiS_Pr.SiS_CHOverScan = -1;
	ivideo->SiS_Pr.SiS_ChSW = false;
	ivideo->SiS_Pr.SiS_UseLCDA = false;
	ivideo->SiS_Pr.HaveEMI = false;
	ivideo->SiS_Pr.HaveEMILCD = false;
	ivideo->SiS_Pr.OverruleEMI = false;
	ivideo->SiS_Pr.SiS_SensibleSR11 = false;
	ivideo->SiS_Pr.SiS_MyCR63 = 0x63;
	ivideo->SiS_Pr.PDC  = -1;
	ivideo->SiS_Pr.PDCA = -1;
	ivideo->SiS_Pr.DDCPortMixup = false;
#अगर_घोषित CONFIG_FB_SIS_315
	अगर(ivideo->chip >= SIS_330) अणु
		ivideo->SiS_Pr.SiS_MyCR63 = 0x53;
		अगर(ivideo->chip >= SIS_661) अणु
			ivideo->SiS_Pr.SiS_SensibleSR11 = true;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	स_नकल(&ivideo->शेष_var, &my_शेष_var, माप(my_शेष_var));

	pci_set_drvdata(pdev, ivideo);

	/* Patch special हालs */
	अगर((ivideo->nbridge = sisfb_get_northbridge(ivideo->chip))) अणु
		चयन(ivideo->nbridge->device) अणु
#अगर_घोषित CONFIG_FB_SIS_300
		हाल PCI_DEVICE_ID_SI_730:
			ivideo->chip = SIS_730;
			म_नकल(ivideo->myid, "SiS 730");
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
		हाल PCI_DEVICE_ID_SI_651:
			/* ivideo->chip is ok */
			म_नकल(ivideo->myid, "SiS 651");
			अवरोध;
		हाल PCI_DEVICE_ID_SI_740:
			ivideo->chip = SIS_740;
			म_नकल(ivideo->myid, "SiS 740");
			अवरोध;
		हाल PCI_DEVICE_ID_SI_661:
			ivideo->chip = SIS_661;
			म_नकल(ivideo->myid, "SiS 661");
			अवरोध;
		हाल PCI_DEVICE_ID_SI_741:
			ivideo->chip = SIS_741;
			म_नकल(ivideo->myid, "SiS 741");
			अवरोध;
		हाल PCI_DEVICE_ID_SI_760:
			ivideo->chip = SIS_760;
			म_नकल(ivideo->myid, "SiS 760");
			अवरोध;
		हाल PCI_DEVICE_ID_SI_761:
			ivideo->chip = SIS_761;
			म_नकल(ivideo->myid, "SiS 761");
			अवरोध;
#पूर्ण_अगर
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ivideo->SiS_Pr.ChipType = ivideo->chip;

	ivideo->SiS_Pr.ivideo = (व्योम *)ivideo;

#अगर_घोषित CONFIG_FB_SIS_315
	अगर((ivideo->SiS_Pr.ChipType == SIS_315PRO) ||
	   (ivideo->SiS_Pr.ChipType == SIS_315)) अणु
		ivideo->SiS_Pr.ChipType = SIS_315H;
	पूर्ण
#पूर्ण_अगर

	अगर(!ivideo->sisvga_enabled) अणु
		अगर(pci_enable_device(pdev)) अणु
			pci_dev_put(ivideo->nbridge);
			framebuffer_release(sis_fb_info);
			वापस -EIO;
		पूर्ण
	पूर्ण

	ivideo->video_base = pci_resource_start(pdev, 0);
	ivideo->video_size = pci_resource_len(pdev, 0);
	ivideo->mmio_base  = pci_resource_start(pdev, 1);
	ivideo->mmio_size  = pci_resource_len(pdev, 1);
	ivideo->SiS_Pr.RelIO = pci_resource_start(pdev, 2) + 0x30;
	ivideo->SiS_Pr.IOAddress = ivideo->vga_base = ivideo->SiS_Pr.RelIO;

	SiSRegInit(&ivideo->SiS_Pr, ivideo->SiS_Pr.IOAddress);

#अगर_घोषित CONFIG_FB_SIS_300
	/* Find PCI प्रणालीs क्रम Chrontel/GPIO communication setup */
	अगर(ivideo->chip == SIS_630) अणु
		i = 0;
        	करो अणु
			अगर(mychswtable[i].subsysVenकरोr == ivideo->subsysvenकरोr &&
			   mychswtable[i].subsysCard   == ivideo->subsysdevice) अणु
				ivideo->SiS_Pr.SiS_ChSW = true;
				prपूर्णांकk(KERN_DEBUG "sisfb: Identified [%s %s] "
					"requiring Chrontel/GPIO setup\n",
					mychswtable[i].venकरोrName,
					mychswtable[i].cardName);
				ivideo->lpcdev = pci_get_device(PCI_VENDOR_ID_SI, 0x0008, शून्य);
				अवरोध;
			पूर्ण
			i++;
		पूर्ण जबतक(mychswtable[i].subsysVenकरोr != 0);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
	अगर((ivideo->chip == SIS_760) && (ivideo->nbridge)) अणु
		ivideo->lpcdev = pci_get_slot(ivideo->nbridge->bus, (2 << 3));
	पूर्ण
#पूर्ण_अगर

	SiS_SetReg(SISSR, 0x05, 0x86);

	अगर( (!ivideo->sisvga_enabled)
#अगर !defined(__i386__) && !defined(__x86_64__)
			      || (sisfb_resetcard)
#पूर्ण_अगर
						   ) अणु
		क्रम(i = 0x30; i <= 0x3f; i++) अणु
			SiS_SetReg(SISCR, i, 0x00);
		पूर्ण
	पूर्ण

	/* Find out about current video mode */
	ivideo->modeprechange = 0x03;
	reg = SiS_GetReg(SISCR, 0x34);
	अगर(reg & 0x7f) अणु
		ivideo->modeprechange = reg & 0x7f;
	पूर्ण अन्यथा अगर(ivideo->sisvga_enabled) अणु
#अगर defined(__i386__) || defined(__x86_64__)
		अचिन्हित अक्षर __iomem *tt = ioremap(0x400, 0x100);
		अगर(tt) अणु
			ivideo->modeprechange = पढ़ोb(tt + 0x49);
			iounmap(tt);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Search and copy ROM image */
	ivideo->bios_abase = शून्य;
	ivideo->SiS_Pr.VirtualRomBase = शून्य;
	ivideo->SiS_Pr.UseROM = false;
	ivideo->haveXGIROM = ivideo->SiS_Pr.SiS_XGIROM = false;
	अगर(ivideo->sisfb_userom) अणु
		ivideo->SiS_Pr.VirtualRomBase = sisfb_find_rom(pdev);
		ivideo->bios_abase = ivideo->SiS_Pr.VirtualRomBase;
		ivideo->SiS_Pr.UseROM = (bool)(ivideo->SiS_Pr.VirtualRomBase);
		prपूर्णांकk(KERN_INFO "sisfb: Video ROM %sfound\n",
			ivideo->SiS_Pr.UseROM ? "" : "not ");
		अगर((ivideo->SiS_Pr.UseROM) && (ivideo->chip >= XGI_20)) अणु
		   ivideo->SiS_Pr.UseROM = false;
		   ivideo->haveXGIROM = ivideo->SiS_Pr.SiS_XGIROM = true;
		   अगर( (ivideo->revision_id == 2) &&
		       (!(ivideo->bios_abase[0x1d1] & 0x01)) ) अणु
			ivideo->SiS_Pr.DDCPortMixup = true;
		   पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "sisfb: Video ROM usage disabled\n");
	पूर्ण

	/* Find प्रणालीs क्रम special custom timing */
	अगर(ivideo->SiS_Pr.SiS_CustomT == CUT_NONE) अणु
		sisfb_detect_custom_timing(ivideo);
	पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
	अगर (ivideo->chip == XGI_20) अणु
		/* Check अगर our Z7 chip is actually Z9 */
		SiS_SetRegOR(SISCR, 0x4a, 0x40);	/* GPIOG EN */
		reg = SiS_GetReg(SISCR, 0x48);
		अगर (reg & 0x02) अणु			/* GPIOG */
			ivideo->chip_real_id = XGI_21;
			dev_info(&pdev->dev, "Z9 detected\n");
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* POST card in हाल this has not been करोne by the BIOS */
	अगर( (!ivideo->sisvga_enabled)
#अगर !defined(__i386__) && !defined(__x86_64__)
			     || (sisfb_resetcard)
#पूर्ण_अगर
						 ) अणु
#अगर_घोषित CONFIG_FB_SIS_300
		अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
			अगर(ivideo->chip == SIS_300) अणु
				sisfb_post_sis300(pdev);
				ivideo->sisfb_can_post = 1;
			पूर्ण
		पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
		अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
			पूर्णांक result = 1;
		/*	अगर((ivideo->chip == SIS_315H)   ||
			   (ivideo->chip == SIS_315)    ||
			   (ivideo->chip == SIS_315PRO) ||
			   (ivideo->chip == SIS_330)) अणु
				sisfb_post_sis315330(pdev);
			पूर्ण अन्यथा */ अगर(ivideo->chip == XGI_20) अणु
				result = sisfb_post_xgi(pdev);
				ivideo->sisfb_can_post = 1;
			पूर्ण अन्यथा अगर((ivideo->chip == XGI_40) && ivideo->haveXGIROM) अणु
				result = sisfb_post_xgi(pdev);
				ivideo->sisfb_can_post = 1;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_INFO "sisfb: Card is not "
					"POSTed and sisfb can't do this either.\n");
			पूर्ण
			अगर(!result) अणु
				prपूर्णांकk(KERN_ERR "sisfb: Failed to POST card\n");
				ret = -ENODEV;
				जाओ error_3;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	ivideo->sisfb_card_posted = 1;

	/* Find out about RAM size */
	अगर(sisfb_get_dram_size(ivideo)) अणु
		prपूर्णांकk(KERN_INFO "sisfb: Fatal error: Unable to determine VRAM size.\n");
		ret = -ENODEV;
		जाओ error_3;
	पूर्ण


	/* Enable PCI addressing and MMIO */
	अगर((ivideo->sisfb_mode_idx < 0) ||
	   ((sisbios_mode[ivideo->sisfb_mode_idx].mode_no[ivideo->mni]) != 0xFF)) अणु
		/* Enable PCI_LINEAR_ADDRESSING and MMIO_ENABLE  */
		SiS_SetRegOR(SISSR, IND_SIS_PCI_ADDRESS_SET, (SIS_PCI_ADDR_ENABLE | SIS_MEM_MAP_IO_ENABLE));
		/* Enable 2D accelerator engine */
		SiS_SetRegOR(SISSR, IND_SIS_MODULE_ENABLE, SIS_ENABLE_2D);
	पूर्ण

	अगर(sisfb_pdc != 0xff) अणु
		अगर(ivideo->sisvga_engine == SIS_300_VGA)
			sisfb_pdc &= 0x3c;
		अन्यथा
			sisfb_pdc &= 0x1f;
		ivideo->SiS_Pr.PDC = sisfb_pdc;
	पूर्ण
#अगर_घोषित CONFIG_FB_SIS_315
	अगर(ivideo->sisvga_engine == SIS_315_VGA) अणु
		अगर(sisfb_pdca != 0xff)
			ivideo->SiS_Pr.PDCA = sisfb_pdca & 0x1f;
	पूर्ण
#पूर्ण_अगर

	अगर(!request_mem_region(ivideo->video_base, ivideo->video_size, "sisfb FB")) अणु
		prपूर्णांकk(KERN_ERR "sisfb: Fatal error: Unable to reserve %dMB framebuffer memory\n",
				(पूर्णांक)(ivideo->video_size >> 20));
		prपूर्णांकk(KERN_ERR "sisfb: Is there another framebuffer driver active?\n");
		ret = -ENODEV;
		जाओ error_3;
	पूर्ण

	अगर(!request_mem_region(ivideo->mmio_base, ivideo->mmio_size, "sisfb MMIO")) अणु
		prपूर्णांकk(KERN_ERR "sisfb: Fatal error: Unable to reserve MMIO region\n");
		ret = -ENODEV;
		जाओ error_2;
	पूर्ण

	ivideo->video_vbase = ioremap_wc(ivideo->video_base, ivideo->video_size);
	ivideo->SiS_Pr.VideoMemoryAddress = ivideo->video_vbase;
	अगर(!ivideo->video_vbase) अणु
		prपूर्णांकk(KERN_ERR "sisfb: Fatal error: Unable to map framebuffer memory\n");
		ret = -ENODEV;
		जाओ error_1;
	पूर्ण

	ivideo->mmio_vbase = ioremap(ivideo->mmio_base, ivideo->mmio_size);
	अगर(!ivideo->mmio_vbase) अणु
		prपूर्णांकk(KERN_ERR "sisfb: Fatal error: Unable to map MMIO region\n");
		ret = -ENODEV;
error_0:	iounmap(ivideo->video_vbase);
error_1:	release_mem_region(ivideo->video_base, ivideo->video_size);
error_2:	release_mem_region(ivideo->mmio_base, ivideo->mmio_size);
error_3:	vमुक्त(ivideo->bios_abase);
		pci_dev_put(ivideo->lpcdev);
		pci_dev_put(ivideo->nbridge);
		अगर(!ivideo->sisvga_enabled)
			pci_disable_device(pdev);
		framebuffer_release(sis_fb_info);
		वापस ret;
	पूर्ण

	prपूर्णांकk(KERN_INFO "sisfb: Video RAM at 0x%lx, mapped to 0x%lx, size %ldk\n",
		ivideo->video_base, (अचिन्हित दीर्घ)ivideo->video_vbase, ivideo->video_size / 1024);

	अगर(ivideo->video_offset) अणु
		prपूर्णांकk(KERN_INFO "sisfb: Viewport offset %ldk\n",
			ivideo->video_offset / 1024);
	पूर्ण

	prपूर्णांकk(KERN_INFO "sisfb: MMIO at 0x%lx, mapped to 0x%lx, size %ldk\n",
		ivideo->mmio_base, (अचिन्हित दीर्घ)ivideo->mmio_vbase, ivideo->mmio_size / 1024);


	/* Determine the size of the command queue */
	अगर(ivideo->sisvga_engine == SIS_300_VGA) अणु
		ivideo->cmdQueueSize = TURBO_QUEUE_AREA_SIZE;
	पूर्ण अन्यथा अणु
		अगर(ivideo->chip == XGI_20) अणु
			ivideo->cmdQueueSize = COMMAND_QUEUE_AREA_SIZE_Z7;
		पूर्ण अन्यथा अणु
			ivideo->cmdQueueSize = COMMAND_QUEUE_AREA_SIZE;
		पूर्ण
	पूर्ण

	/* Engines are no दीर्घer initialized here; this is
	 * now करोne after the first mode-चयन (अगर the
	 * submitted var has its acceleration flags set).
	 */

	/* Calculate the base of the (unused) hw cursor */
	ivideo->hwcursor_vbase = ivideo->video_vbase
				 + ivideo->video_size
				 - ivideo->cmdQueueSize
				 - ivideo->hwcursor_size;
	ivideo->caps |= HW_CURSOR_CAP;

	/* Initialize offscreen memory manager */
	अगर((ivideo->havenoheap = sisfb_heap_init(ivideo))) अणु
		prपूर्णांकk(KERN_WARNING "sisfb: Failed to initialize offscreen memory heap\n");
	पूर्ण

	/* Used क्रम clearing the screen only, thereक्रमe respect our mem limit */
	ivideo->SiS_Pr.VideoMemoryAddress += ivideo->video_offset;
	ivideo->SiS_Pr.VideoMemorySize = ivideo->sisfb_mem;

	ivideo->vbflags = 0;
	ivideo->lcddeभ_शेषeidx = DEFAULT_LCDMODE;
	ivideo->tvdeभ_शेषeidx  = DEFAULT_TVMODE;
	ivideo->deभ_शेषeidx    = DEFAULT_MODE;

	ivideo->newrom = 0;
	अगर(ivideo->chip < XGI_20) अणु
		अगर(ivideo->bios_abase) अणु
			ivideo->newrom = SiSDetermineROMLayout661(&ivideo->SiS_Pr);
		पूर्ण
	पूर्ण

	अगर((ivideo->sisfb_mode_idx < 0) ||
	   ((sisbios_mode[ivideo->sisfb_mode_idx].mode_no[ivideo->mni]) != 0xFF)) अणु

		sisfb_sense_crt1(ivideo);

		sisfb_get_VB_type(ivideo);

		अगर(ivideo->vbflags2 & VB2_VIDEOBRIDGE) अणु
			sisfb_detect_VB_connect(ivideo);
		पूर्ण

		ivideo->currentvbflags = ivideo->vbflags & (VB_VIDEOBRIDGE | TV_STANDARD);

		/* Decide on which CRT2 device to use */
		अगर(ivideo->vbflags2 & VB2_VIDEOBRIDGE) अणु
			अगर(ivideo->sisfb_crt2type != -1) अणु
				अगर((ivideo->sisfb_crt2type == CRT2_LCD) &&
				   (ivideo->vbflags & CRT2_LCD)) अणु
					ivideo->currentvbflags |= CRT2_LCD;
				पूर्ण अन्यथा अगर(ivideo->sisfb_crt2type != CRT2_LCD) अणु
					ivideo->currentvbflags |= ivideo->sisfb_crt2type;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Chrontel 700x TV detection often unreliable, thereक्रमe
				 * use a dअगरferent शेष order on such machines
				 */
				अगर((ivideo->sisvga_engine == SIS_300_VGA) &&
				   (ivideo->vbflags2 & VB2_CHRONTEL)) अणु
					अगर(ivideo->vbflags & CRT2_LCD)
						ivideo->currentvbflags |= CRT2_LCD;
					अन्यथा अगर(ivideo->vbflags & CRT2_TV)
						ivideo->currentvbflags |= CRT2_TV;
					अन्यथा अगर(ivideo->vbflags & CRT2_VGA)
						ivideo->currentvbflags |= CRT2_VGA;
				पूर्ण अन्यथा अणु
					अगर(ivideo->vbflags & CRT2_TV)
						ivideo->currentvbflags |= CRT2_TV;
					अन्यथा अगर(ivideo->vbflags & CRT2_LCD)
						ivideo->currentvbflags |= CRT2_LCD;
					अन्यथा अगर(ivideo->vbflags & CRT2_VGA)
						ivideo->currentvbflags |= CRT2_VGA;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर(ivideo->vbflags & CRT2_LCD) अणु
			sisfb_detect_lcd_type(ivideo);
		पूर्ण

		sisfb_save_pdc_emi(ivideo);

		अगर(!ivideo->sisfb_crt1off) अणु
			sisfb_handle_ddc(ivideo, &ivideo->sisfb_thismonitor, 0);
		पूर्ण अन्यथा अणु
			अगर((ivideo->vbflags2 & VB2_SISTMDSBRIDGE) &&
			   (ivideo->vbflags & (CRT2_VGA | CRT2_LCD))) अणु
				sisfb_handle_ddc(ivideo, &ivideo->sisfb_thismonitor, 1);
			पूर्ण
		पूर्ण

		अगर(ivideo->sisfb_mode_idx >= 0) अणु
			पूर्णांक bu = ivideo->sisfb_mode_idx;
			ivideo->sisfb_mode_idx = sisfb_validate_mode(ivideo,
					ivideo->sisfb_mode_idx, ivideo->currentvbflags);
			अगर(bu != ivideo->sisfb_mode_idx) अणु
				prपूर्णांकk(KERN_ERR "Mode %dx%dx%d failed validation\n",
					sisbios_mode[bu].xres,
					sisbios_mode[bu].yres,
					sisbios_mode[bu].bpp);
			पूर्ण
		पूर्ण

		अगर(ivideo->sisfb_mode_idx < 0) अणु
			चयन(ivideo->currentvbflags & VB_DISPTYPE_DISP2) अणु
			   हाल CRT2_LCD:
				ivideo->sisfb_mode_idx = ivideo->lcddeभ_शेषeidx;
				अवरोध;
			   हाल CRT2_TV:
				ivideo->sisfb_mode_idx = ivideo->tvdeभ_शेषeidx;
				अवरोध;
			   शेष:
				ivideo->sisfb_mode_idx = ivideo->deभ_शेषeidx;
				अवरोध;
			पूर्ण
		पूर्ण

		ivideo->mode_no = sisbios_mode[ivideo->sisfb_mode_idx].mode_no[ivideo->mni];

		अगर(ivideo->refresh_rate != 0) अणु
			sisfb_search_refresh_rate(ivideo, ivideo->refresh_rate,
						ivideo->sisfb_mode_idx);
		पूर्ण

		अगर(ivideo->rate_idx == 0) अणु
			ivideo->rate_idx = sisbios_mode[ivideo->sisfb_mode_idx].rate_idx;
			ivideo->refresh_rate = 60;
		पूर्ण

		अगर(ivideo->sisfb_thismonitor.datavalid) अणु
			अगर(!sisfb_verअगरy_rate(ivideo, &ivideo->sisfb_thismonitor,
						ivideo->sisfb_mode_idx,
						ivideo->rate_idx,
						ivideo->refresh_rate)) अणु
				prपूर्णांकk(KERN_INFO "sisfb: WARNING: Refresh rate "
							"exceeds monitor specs!\n");
			पूर्ण
		पूर्ण

		ivideo->video_bpp = sisbios_mode[ivideo->sisfb_mode_idx].bpp;
		ivideo->video_width = sisbios_mode[ivideo->sisfb_mode_idx].xres;
		ivideo->video_height = sisbios_mode[ivideo->sisfb_mode_idx].yres;

		sisfb_set_vparms(ivideo);

		prपूर्णांकk(KERN_INFO "sisfb: Default mode is %dx%dx%d (%dHz)\n",
			ivideo->video_width, ivideo->video_height, ivideo->video_bpp,
			ivideo->refresh_rate);

		/* Set up the शेष var according to chosen शेष display mode */
		ivideo->शेष_var.xres = ivideo->शेष_var.xres_भव = ivideo->video_width;
		ivideo->शेष_var.yres = ivideo->शेष_var.yres_भव = ivideo->video_height;
		ivideo->शेष_var.bits_per_pixel = ivideo->video_bpp;

		sisfb_bpp_to_var(ivideo, &ivideo->शेष_var);

		ivideo->शेष_var.pixघड़ी = (u32) (1000000000 /
			sisfb_mode_rate_to_dघड़ी(&ivideo->SiS_Pr, ivideo->mode_no, ivideo->rate_idx));

		अगर(sisfb_mode_rate_to_ddata(&ivideo->SiS_Pr, ivideo->mode_no,
						ivideo->rate_idx, &ivideo->शेष_var)) अणु
			अगर((ivideo->शेष_var.vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE) अणु
				ivideo->शेष_var.pixघड़ी <<= 1;
			पूर्ण
		पूर्ण

		अगर(ivideo->sisfb_ypan) अणु
			/* Maximize regardless of sisfb_max at startup */
			ivideo->शेष_var.yres_भव =
				sisfb_calc_maxyres(ivideo, &ivideo->शेष_var);
			अगर(ivideo->शेष_var.yres_भव < ivideo->शेष_var.yres) अणु
				ivideo->शेष_var.yres_भव = ivideo->शेष_var.yres;
			पूर्ण
		पूर्ण

		sisfb_calc_pitch(ivideo, &ivideo->शेष_var);

		ivideo->accel = 0;
		अगर(ivideo->sisfb_accel) अणु
			ivideo->accel = -1;
#अगर_घोषित STUPID_ACCELF_TEXT_SHIT
			ivideo->शेष_var.accel_flags |= FB_ACCELF_TEXT;
#पूर्ण_अगर
		पूर्ण
		sisfb_initaccel(ivideo);

#अगर defined(FBINFO_HWACCEL_DISABLED) && defined(FBINFO_HWACCEL_XPAN)
		sis_fb_info->flags = FBINFO_DEFAULT 		|
				     FBINFO_HWACCEL_YPAN 	|
				     FBINFO_HWACCEL_XPAN 	|
				     FBINFO_HWACCEL_COPYAREA 	|
				     FBINFO_HWACCEL_FILLRECT 	|
				     ((ivideo->accel) ? 0 : FBINFO_HWACCEL_DISABLED);
#अन्यथा
		sis_fb_info->flags = FBINFO_FLAG_DEFAULT;
#पूर्ण_अगर
		sis_fb_info->var = ivideo->शेष_var;
		sis_fb_info->fix = ivideo->sisfb_fix;
		sis_fb_info->screen_base = ivideo->video_vbase + ivideo->video_offset;
		sis_fb_info->fbops = &sisfb_ops;
		sis_fb_info->pseuकरो_palette = ivideo->pseuकरो_palette;

		fb_alloc_cmap(&sis_fb_info->cmap, 256 , 0);

		prपूर्णांकk(KERN_DEBUG "sisfb: Initial vbflags 0x%x\n", (पूर्णांक)ivideo->vbflags);

		ivideo->wc_cookie = arch_phys_wc_add(ivideo->video_base,
						     ivideo->video_size);
		अगर(रेजिस्टर_framebuffer(sis_fb_info) < 0) अणु
			prपूर्णांकk(KERN_ERR "sisfb: Fatal error: Failed to register framebuffer\n");
			ret = -EINVAL;
			iounmap(ivideo->mmio_vbase);
			जाओ error_0;
		पूर्ण

		ivideo->रेजिस्टरed = 1;

		/* Enlist us */
		ivideo->next = card_list;
		card_list = ivideo;

		prपूर्णांकk(KERN_INFO "sisfb: 2D acceleration is %s, y-panning %s\n",
			ivideo->sisfb_accel ? "enabled" : "disabled",
			ivideo->sisfb_ypan  ?
				(ivideo->sisfb_max ? "enabled (auto-max)" :
						"enabled (no auto-max)") :
									"disabled");


		fb_info(sis_fb_info, "%s frame buffer device version %d.%d.%d\n",
			ivideo->myid, VER_MAJOR, VER_MINOR, VER_LEVEL);

		prपूर्णांकk(KERN_INFO "sisfb: Copyright (C) 2001-2005 Thomas Winischhofer\n");

	पूर्ण	/* अगर mode = "none" */

	वापस 0;
पूर्ण

/*****************************************************/
/*                PCI DEVICE HANDLING                */
/*****************************************************/

अटल व्योम sisfb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sis_video_info	*ivideo = pci_get_drvdata(pdev);
	काष्ठा fb_info		*sis_fb_info = ivideo->memyselfandi;
	पूर्णांक			रेजिस्टरed = ivideo->रेजिस्टरed;
	पूर्णांक			modechanged = ivideo->modechanged;

	/* Unmap */
	iounmap(ivideo->mmio_vbase);
	iounmap(ivideo->video_vbase);

	/* Release mem regions */
	release_mem_region(ivideo->video_base, ivideo->video_size);
	release_mem_region(ivideo->mmio_base, ivideo->mmio_size);

	vमुक्त(ivideo->bios_abase);

	pci_dev_put(ivideo->lpcdev);

	pci_dev_put(ivideo->nbridge);

	arch_phys_wc_del(ivideo->wc_cookie);

	/* If device was disabled when starting, disable
	 * it when quitting.
	 */
	अगर(!ivideo->sisvga_enabled)
		pci_disable_device(pdev);

	/* Unरेजिस्टर the framebuffer */
	अगर(ivideo->रेजिस्टरed) अणु
		unरेजिस्टर_framebuffer(sis_fb_info);
		framebuffer_release(sis_fb_info);
	पूर्ण

	/* OK, our ivideo is gone क्रम good from here. */

	/* TODO: Restore the initial mode
	 * This sounds easy but is as good as impossible
	 * on many machines with SiS chip and video bridge
	 * since text modes are always set up dअगरferently
	 * from machine to machine. Depends on the type
	 * of पूर्णांकegration between chipset and bridge.
	 */
	अगर(रेजिस्टरed && modechanged)
		prपूर्णांकk(KERN_INFO
			"sisfb: Restoring of text mode not supported yet\n");
पूर्ण;

अटल काष्ठा pci_driver sisfb_driver = अणु
	.name		= "sisfb",
	.id_table 	= sisfb_pci_table,
	.probe		= sisfb_probe,
	.हटाओ 	= sisfb_हटाओ,
पूर्ण;

अटल पूर्णांक __init sisfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *options = शून्य;

	अगर(fb_get_options("sisfb", &options))
		वापस -ENODEV;

	sisfb_setup(options);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&sisfb_driver);
पूर्ण

#अगर_अघोषित MODULE
module_init(sisfb_init);
#पूर्ण_अगर

/*****************************************************/
/*                      MODULE                       */
/*****************************************************/

#अगर_घोषित MODULE

अटल अक्षर		*mode = शून्य;
अटल पूर्णांक		vesa = -1;
अटल अचिन्हित पूर्णांक	rate = 0;
अटल अचिन्हित पूर्णांक	crt1off = 1;
अटल अचिन्हित पूर्णांक	mem = 0;
अटल अक्षर		*क्रमcecrt2type = शून्य;
अटल पूर्णांक		क्रमcecrt1 = -1;
अटल पूर्णांक		pdc = -1;
अटल पूर्णांक		pdc1 = -1;
अटल पूर्णांक		noaccel = -1;
अटल पूर्णांक		noypan  = -1;
अटल पूर्णांक		nomax = -1;
अटल पूर्णांक		userom = -1;
अटल पूर्णांक		useoem = -1;
अटल अक्षर		*tvstandard = शून्य;
अटल पूर्णांक		nocrt2rate = 0;
अटल पूर्णांक		scalelcd = -1;
अटल अक्षर		*specialtiming = शून्य;
अटल पूर्णांक		lvdshl = -1;
अटल पूर्णांक		tvxposoffset = 0, tvyposoffset = 0;
#अगर !defined(__i386__) && !defined(__x86_64__)
अटल पूर्णांक		resetcard = 0;
अटल पूर्णांक		videoram = 0;
#पूर्ण_अगर

अटल पूर्णांक __init sisfb_init_module(व्योम)
अणु
	sisfb_setशेषparms();

	अगर(rate)
		sisfb_parm_rate = rate;

	अगर((scalelcd == 0) || (scalelcd == 1))
		sisfb_scalelcd = scalelcd ^ 1;

	/* Need to check crt2 type first क्रम fstn/dstn */

	अगर(क्रमcecrt2type)
		sisfb_search_crt2type(क्रमcecrt2type);

	अगर(tvstandard)
		sisfb_search_tvstd(tvstandard);

	अगर(mode)
		sisfb_search_mode(mode, false);
	अन्यथा अगर(vesa != -1)
		sisfb_search_vesamode(vesa, false);

	sisfb_crt1off = (crt1off == 0) ? 1 : 0;

	sisfb_क्रमcecrt1 = क्रमcecrt1;
	अगर(क्रमcecrt1 == 1)
		sisfb_crt1off = 0;
	अन्यथा अगर(क्रमcecrt1 == 0)
		sisfb_crt1off = 1;

	अगर(noaccel == 1)
		sisfb_accel = 0;
	अन्यथा अगर(noaccel == 0)
		sisfb_accel = 1;

	अगर(noypan == 1)
		sisfb_ypan = 0;
	अन्यथा अगर(noypan == 0)
		sisfb_ypan = 1;

	अगर(nomax == 1)
		sisfb_max = 0;
	अन्यथा अगर(nomax == 0)
		sisfb_max = 1;

	अगर(mem)
		sisfb_parm_mem = mem;

	अगर(userom != -1)
		sisfb_userom = userom;

	अगर(useoem != -1)
		sisfb_useoem = useoem;

        अगर(pdc != -1)
		sisfb_pdc  = (pdc  & 0x7f);

	अगर(pdc1 != -1)
		sisfb_pdca = (pdc1 & 0x1f);

	sisfb_nocrt2rate = nocrt2rate;

	अगर(specialtiming)
		sisfb_search_specialtiming(specialtiming);

	अगर((lvdshl >= 0) && (lvdshl <= 3))
		sisfb_lvdshl = lvdshl;

	sisfb_tvxposoffset = tvxposoffset;
	sisfb_tvyposoffset = tvyposoffset;

#अगर !defined(__i386__) && !defined(__x86_64__)
	sisfb_resetcard = (resetcard) ? 1 : 0;
	अगर(videoram)
		sisfb_videoram = videoram;
#पूर्ण_अगर

	वापस sisfb_init();
पूर्ण

अटल व्योम __निकास sisfb_हटाओ_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sisfb_driver);
	prपूर्णांकk(KERN_DEBUG "sisfb: Module unloaded\n");
पूर्ण

module_init(sisfb_init_module);
module_निकास(sisfb_हटाओ_module);

MODULE_DESCRIPTION("SiS 300/540/630/730/315/55x/65x/661/74x/330/76x/34x, XGI V3XT/V5/V8/Z7 framebuffer device driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Winischhofer <thomas@winischhofer.net>, Others");

module_param(mem, पूर्णांक, 0);
module_param(noaccel, पूर्णांक, 0);
module_param(noypan, पूर्णांक, 0);
module_param(nomax, पूर्णांक, 0);
module_param(userom, पूर्णांक, 0);
module_param(useoem, पूर्णांक, 0);
module_param(mode, अक्षरp, 0);
module_param(vesa, पूर्णांक, 0);
module_param(rate, पूर्णांक, 0);
module_param(क्रमcecrt1, पूर्णांक, 0);
module_param(क्रमcecrt2type, अक्षरp, 0);
module_param(scalelcd, पूर्णांक, 0);
module_param(pdc, पूर्णांक, 0);
module_param(pdc1, पूर्णांक, 0);
module_param(specialtiming, अक्षरp, 0);
module_param(lvdshl, पूर्णांक, 0);
module_param(tvstandard, अक्षरp, 0);
module_param(tvxposoffset, पूर्णांक, 0);
module_param(tvyposoffset, पूर्णांक, 0);
module_param(nocrt2rate, पूर्णांक, 0);
#अगर !defined(__i386__) && !defined(__x86_64__)
module_param(resetcard, पूर्णांक, 0);
module_param(videoram, पूर्णांक, 0);
#पूर्ण_अगर

MODULE_PARM_DESC(mem,
	"\nDetermines the beginning of the video memory heap in KB. This heap is used\n"
	  "for video RAM management for eg. DRM/DRI. On 300 series, the default depends\n"
	  "on the amount of video RAM available. If 8MB of video RAM or less is available,\n"
	  "the heap starts at 4096KB, if between 8 and 16MB are available at 8192KB,\n"
	  "otherwise at 12288KB. On 315/330/340 series, the heap size is 32KB by default.\n"
	  "The value is to be specified without 'KB'.\n");

MODULE_PARM_DESC(noaccel,
	"\nIf set to anything other than 0, 2D acceleration will be disabled.\n"
	  "(default: 0)\n");

MODULE_PARM_DESC(noypan,
	"\nIf set to anything other than 0, y-panning will be disabled and scrolling\n"
	  "will be performed by redrawing the screen. (default: 0)\n");

MODULE_PARM_DESC(nomax,
	"\nIf y-panning is enabled, sisfb will by default use the entire available video\n"
	  "memory for the virtual screen in order to optimize scrolling performance. If\n"
	  "this is set to anything other than 0, sisfb will not do this and thereby \n"
	  "enable the user to positively specify a virtual Y size of the screen using\n"
	  "fbset. (default: 0)\n");

MODULE_PARM_DESC(mode,
	"\nSelects the desired default display mode in the format XxYxDepth,\n"
	 "eg. 1024x768x16. Other formats supported include XxY-Depth and\n"
	 "XxY-Depth@Rate. If the parameter is only one (decimal or hexadecimal)\n"
	 "number, it will be interpreted as a VESA mode number. (default: 800x600x8)\n");

MODULE_PARM_DESC(vesa,
	"\nSelects the desired default display mode by VESA defined mode number, eg.\n"
	 "0x117 (default: 0x0103)\n");

MODULE_PARM_DESC(rate,
	"\nSelects the desired vertical refresh rate for CRT1 (external VGA) in Hz.\n"
	  "If the mode is specified in the format XxY-Depth@Rate, this parameter\n"
	  "will be ignored (default: 60)\n");

MODULE_PARM_DESC(क्रमcecrt1,
	"\nNormally, the driver autodetects whether or not CRT1 (external VGA) is \n"
	  "connected. With this option, the detection can be overridden (1=CRT1 ON,\n"
	  "0=CRT1 OFF) (default: [autodetected])\n");

MODULE_PARM_DESC(क्रमcecrt2type,
	"\nIf this option is omitted, the driver autodetects CRT2 output devices, such as\n"
	  "LCD, TV or secondary VGA. With this option, this autodetection can be\n"
	  "overridden. Possible parameters are LCD, TV, VGA or NONE. NONE disables CRT2.\n"
	  "On systems with a SiS video bridge, parameters SVIDEO, COMPOSITE or SCART can\n"
	  "be used instead of TV to override the TV detection. Furthermore, on systems\n"
	  "with a SiS video bridge, SVIDEO+COMPOSITE, HIVISION, YPBPR480I, YPBPR480P,\n"
	  "YPBPR720P and YPBPR1080I are understood. However, whether or not these work\n"
	  "depends on the very hardware in use. (default: [autodetected])\n");

MODULE_PARM_DESC(scalelcd,
	"\nSetting this to 1 will force the driver to scale the LCD image to the panel's\n"
	  "native resolution. Setting it to 0 will disable scaling; LVDS panels will\n"
	  "show black bars around the image, TMDS panels will probably do the scaling\n"
	  "themselves. Default: 1 on LVDS panels, 0 on TMDS panels\n");

MODULE_PARM_DESC(pdc,
	"\nThis is for manually selecting the LCD panel delay compensation. The driver\n"
	  "should detect this correctly in most cases; however, sometimes this is not\n"
	  "possible. If you see 'small waves' on the LCD, try setting this to 4, 32 or 24\n"
	  "on a 300 series chipset; 6 on other chipsets. If the problem persists, try\n"
	  "other values (on 300 series: between 4 and 60 in steps of 4; otherwise: any\n"
	  "value from 0 to 31). (default: autodetected, if LCD is active during start)\n");

#अगर_घोषित CONFIG_FB_SIS_315
MODULE_PARM_DESC(pdc1,
	"\nThis is same as pdc, but for LCD-via CRT1. Hence, this is for the 315/330/340\n"
	  "series only. (default: autodetected if LCD is in LCD-via-CRT1 mode during\n"
	  "startup) - Note: currently, this has no effect because LCD-via-CRT1 is not\n"
	  "implemented yet.\n");
#पूर्ण_अगर

MODULE_PARM_DESC(specialtiming,
	"\nPlease refer to documentation for more information on this option.\n");

MODULE_PARM_DESC(lvdshl,
	"\nPlease refer to documentation for more information on this option.\n");

MODULE_PARM_DESC(tvstandard,
	"\nThis allows overriding the BIOS default for the TV standard. Valid choices are\n"
	  "pal, ntsc, palm and paln. (default: [auto; pal or ntsc only])\n");

MODULE_PARM_DESC(tvxposoffset,
	"\nRelocate TV output horizontally. Possible parameters: -32 through 32.\n"
	  "Default: 0\n");

MODULE_PARM_DESC(tvyposoffset,
	"\nRelocate TV output vertically. Possible parameters: -32 through 32.\n"
	  "Default: 0\n");

MODULE_PARM_DESC(nocrt2rate,
	"\nSetting this to 1 will force the driver to use the default refresh rate for\n"
	  "CRT2 if CRT2 type is VGA. (default: 0, use same rate as CRT1)\n");

#अगर !defined(__i386__) && !defined(__x86_64__)
#अगर_घोषित CONFIG_FB_SIS_300
MODULE_PARM_DESC(resetcard,
	"\nSet this to 1 in order to reset (POST) the card on non-x86 machines where\n"
	  "the BIOS did not POST the card (only supported for SiS 300/305 and XGI cards\n"
	  "currently). Default: 0\n");

MODULE_PARM_DESC(videoram,
	"\nSet this to the amount of video RAM (in kilobyte) the card has. Required on\n"
	  "some non-x86 architectures where the memory auto detection fails. Only\n"
	  "relevant if resetcard is set, too. SiS300/305 only. Default: [auto-detect]\n");
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर 	   /*  /MODULE  */

/* _GPL only क्रम new symbols. */
EXPORT_SYMBOL(sis_दो_स्मृति);
EXPORT_SYMBOL(sis_मुक्त);
EXPORT_SYMBOL_GPL(sis_दो_स्मृति_new);
EXPORT_SYMBOL_GPL(sis_मुक्त_new);



