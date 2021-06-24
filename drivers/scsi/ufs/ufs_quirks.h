<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2016, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _UFS_QUIRKS_H_
#घोषणा _UFS_QUIRKS_H_

/* वापस true अगर s1 is a prefix of s2 */
#घोषणा STR_PRFX_EQUAL(s1, s2) !म_भेदन(s1, s2, म_माप(s1))

#घोषणा UFS_ANY_VENDOR 0xFFFF
#घोषणा UFS_ANY_MODEL  "ANY_MODEL"

#घोषणा UFS_VENDOR_MICRON      0x12C
#घोषणा UFS_VENDOR_SAMSUNG     0x1CE
#घोषणा UFS_VENDOR_SKHYNIX     0x1AD
#घोषणा UFS_VENDOR_TOSHIBA     0x198
#घोषणा UFS_VENDOR_WDC         0x145

/**
 * ufs_dev_fix - ufs device quirk info
 * @card: ufs card details
 * @quirk: device quirk
 */
काष्ठा ufs_dev_fix अणु
	u16 wmanufacturerid;
	u8 *model;
	अचिन्हित पूर्णांक quirk;
पूर्ण;

#घोषणा END_FIX अणु पूर्ण

/* add specअगरic device quirk */
#घोषणा UFS_FIX(_venकरोr, _model, _quirk) अणु \
	.wmanufacturerid = (_venकरोr),\
	.model = (_model),		   \
	.quirk = (_quirk),		   \
पूर्ण

/*
 * Some venकरोr's UFS device sends back to back NACs क्रम the DL data frames
 * causing the host controller to उठाओ the DFES error status. Someबार
 * such UFS devices send back to back NAC without रुकोing क्रम new
 * retransmitted DL frame from the host and in such हालs it might be possible
 * the Host UniPro goes पूर्णांकo bad state without raising the DFES error
 * पूर्णांकerrupt. If this happens then all the pending commands would समयout
 * only after respective SW command (which is generally too large).
 *
 * We can workaround such device behaviour like this:
 * - As soon as SW sees the DL NAC error, it should schedule the error handler
 * - Error handler would sleep क्रम 50ms to see अगर there are any fatal errors
 *   उठाओd by UFS controller.
 *    - If there are fatal errors then SW करोes normal error recovery.
 *    - If there are no fatal errors then SW sends the NOP command to device
 *      to check अगर link is alive.
 *        - If NOP command बार out, SW करोes normal error recovery
 *        - If NOP command succeed, skip the error handling.
 *
 * If DL NAC error is seen multiple बार with some venकरोr's UFS devices then
 * enable this quirk to initiate quick error recovery and also silence related
 * error logs to reduce spamming of kernel logs.
 */
#घोषणा UFS_DEVICE_QUIRK_RECOVERY_FROM_DL_NAC_ERRORS (1 << 2)

/*
 * Few Toshiba UFS device models advertise RX_MIN_ACTIVATETIME_CAPABILITY as
 * 600us which may not be enough क्रम reliable hibern8 निकास hardware sequence
 * from UFS device.
 * To workaround this issue, host should set its PA_TACTIVATE समय to 1ms even
 * अगर device advertises RX_MIN_ACTIVATETIME_CAPABILITY less than 1ms.
 */
#घोषणा UFS_DEVICE_QUIRK_PA_TACTIVATE	(1 << 4)

/*
 * It seems some UFS devices may keep drawing more than sleep current
 * (atleast क्रम 500us) from UFS rails (especially from VCCQ rail).
 * To aव्योम this situation, add 2ms delay beक्रमe putting these UFS
 * rails in LPM mode.
 */
#घोषणा UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM	(1 << 6)

/*
 * Some UFS devices require host PA_TACTIVATE to be lower than device
 * PA_TACTIVATE, enabling this quirk ensure this.
 */
#घोषणा UFS_DEVICE_QUIRK_HOST_PA_TACTIVATE	(1 << 7)

/*
 * The max. value PA_SaveConfigTime is 250 (10us) but this is not enough क्रम
 * some venकरोrs.
 * Gear चयन from PWM to HS may fail even with this max. PA_SaveConfigTime.
 * Gear चयन can be issued by host controller as an error recovery and any
 * software delay will not help on this हाल so we need to increase
 * PA_SaveConfigTime to >32us as per venकरोr recommendation.
 */
#घोषणा UFS_DEVICE_QUIRK_HOST_PA_SAVECONFIGTIME	(1 << 8)

/*
 * Some UFS devices require VS_DebugSaveConfigTime is 0x10,
 * enabling this quirk ensure this.
 */
#घोषणा UFS_DEVICE_QUIRK_HOST_VS_DEBUGSAVECONFIGTIME	(1 << 9)

/*
 * Some pre-3.1 UFS devices can support extended features by upgrading
 * the firmware. Enable this quirk to make UFS core driver probe and enable
 * supported features on such devices.
 */
#घोषणा UFS_DEVICE_QUIRK_SUPPORT_EXTENDED_FEATURES (1 << 10)

/*
 * Some UFS devices require delay after VCC घातer rail is turned-off.
 * Enable this quirk to पूर्णांकroduce 5ms delays after VCC घातer-off during
 * suspend flow.
 */
#घोषणा UFS_DEVICE_QUIRK_DELAY_AFTER_LPM        (1 << 11)

#पूर्ण_अगर /* UFS_QUIRKS_H_ */
