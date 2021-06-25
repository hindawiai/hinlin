<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#समावेश "global.h"

पूर्णांक viafb_ioctl_get_viafb_info(u_दीर्घ arg)
अणु
	काष्ठा viafb_ioctl_info viainfo;

	स_रखो(&viainfo, 0, माप(काष्ठा viafb_ioctl_info));

	viainfo.viafb_id = VIAID;
	viainfo.venकरोr_id = PCI_VIA_VENDOR_ID;

	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_CLE266:
		viainfo.device_id = UNICHROME_CLE266_DID;
		अवरोध;

	हाल UNICHROME_K400:
		viainfo.device_id = UNICHROME_K400_DID;
		अवरोध;

	हाल UNICHROME_K800:
		viainfo.device_id = UNICHROME_K800_DID;
		अवरोध;

	हाल UNICHROME_PM800:
		viainfo.device_id = UNICHROME_PM800_DID;
		अवरोध;

	हाल UNICHROME_CN700:
		viainfo.device_id = UNICHROME_CN700_DID;
		अवरोध;

	हाल UNICHROME_CX700:
		viainfo.device_id = UNICHROME_CX700_DID;
		अवरोध;

	हाल UNICHROME_K8M890:
		viainfo.device_id = UNICHROME_K8M890_DID;
		अवरोध;

	हाल UNICHROME_P4M890:
		viainfo.device_id = UNICHROME_P4M890_DID;
		अवरोध;

	हाल UNICHROME_P4M900:
		viainfo.device_id = UNICHROME_P4M900_DID;
		अवरोध;
	पूर्ण

	viainfo.version = VERSION_MAJOR;
	viainfo.revision = VERSION_MINOR;

	अगर (copy_to_user((व्योम __user *)arg, &viainfo, माप(viainfo)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Hot-Plug Priority: DVI > CRT*/
पूर्णांक viafb_ioctl_hotplug(पूर्णांक hres, पूर्णांक vres, पूर्णांक bpp)
अणु
	पूर्णांक DVIsense, status = 0;
	DEBUG_MSG(KERN_INFO "viafb_ioctl_hotplug!!\n");

	अगर (viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_name !=
		NON_TMDS_TRANSMITTER) अणु
		DVIsense = viafb_dvi_sense();

		अगर (DVIsense) अणु
			DEBUG_MSG(KERN_INFO "DVI Attached...\n");
			अगर (viafb_DeviceStatus != DVI_Device) अणु
				viafb_DVI_ON = 1;
				viafb_CRT_ON = 0;
				viafb_LCD_ON = 0;
				viafb_DeviceStatus = DVI_Device;
				viafb_set_iga_path();
				वापस viafb_DeviceStatus;
			पूर्ण
			status = 1;
		पूर्ण अन्यथा
			DEBUG_MSG(KERN_INFO "DVI De-attached...\n");
	पूर्ण

	अगर ((viafb_DeviceStatus != CRT_Device) && (status == 0)) अणु
		viafb_CRT_ON = 1;
		viafb_DVI_ON = 0;
		viafb_LCD_ON = 0;

		viafb_DeviceStatus = CRT_Device;
		viafb_set_iga_path();
		वापस viafb_DeviceStatus;
	पूर्ण

	वापस 0;
पूर्ण
