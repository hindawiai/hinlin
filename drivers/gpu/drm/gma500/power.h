<शैली गुरु>
/**************************************************************************
 * Copyright (c) 2009-2011, Intel Corporation.
 * All Rights Reserved.

 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Benjamin Defnet <benjamin.r.defnet@पूर्णांकel.com>
 *    Rajesh Poornachandran <rajesh.poornachandran@पूर्णांकel.com>
 * Massively reworked
 *    Alan Cox <alan@linux.पूर्णांकel.com>
 */
#अगर_अघोषित _PSB_POWERMGMT_H_
#घोषणा _PSB_POWERMGMT_H_

#समावेश <linux/pci.h>

काष्ठा device;
काष्ठा drm_device;

व्योम gma_घातer_init(काष्ठा drm_device *dev);
व्योम gma_घातer_uninit(काष्ठा drm_device *dev);

/*
 * The kernel bus घातer management  will call these functions
 */
पूर्णांक gma_घातer_suspend(काष्ठा device *dev);
पूर्णांक gma_घातer_resume(काष्ठा device *dev);
पूर्णांक gma_घातer_thaw(काष्ठा device *dev);
पूर्णांक gma_घातer_मुक्तze(काष्ठा device *dev);
पूर्णांक gma_घातer_restore(काष्ठा device *_dev);

/*
 * These are the functions the driver should use to wrap all hw access
 * (i.e. रेजिस्टर पढ़ोs and ग_लिखोs)
 */
bool gma_घातer_begin(काष्ठा drm_device *dev, bool क्रमce);
व्योम gma_घातer_end(काष्ठा drm_device *dev);

/*
 * Use this function to करो an instantaneous check क्रम अगर the hw is on.
 * Only use this in हालs where you know the mutex is alपढ़ोy held such
 * as in irq install/uninstall and you need to
 * prevent a deadlock situation.  Otherwise use gma_घातer_begin().
 */
bool gma_घातer_is_on(काष्ठा drm_device *dev);

/*
 * GFX-Runसमय PM callbacks
 */
पूर्णांक psb_runसमय_suspend(काष्ठा device *dev);
पूर्णांक psb_runसमय_resume(काष्ठा device *dev);
पूर्णांक psb_runसमय_idle(काष्ठा device *dev);

#पूर्ण_अगर /*_PSB_POWERMGMT_H_*/
