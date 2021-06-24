<शैली गुरु>
/*
 * HDMI header definition क्रम OMAP4 HDMI CEC IP
 *
 * Copyright 2016-2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _HDMI4_CEC_H_
#घोषणा _HDMI4_CEC_H_

काष्ठा hdmi_core_data;
काष्ठा hdmi_wp_data;
काष्ठा platक्रमm_device;

/* HDMI CEC funcs */
#अगर_घोषित CONFIG_OMAP4_DSS_HDMI_CEC
व्योम hdmi4_cec_set_phys_addr(काष्ठा hdmi_core_data *core, u16 pa);
व्योम hdmi4_cec_irq(काष्ठा hdmi_core_data *core);
पूर्णांक hdmi4_cec_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_core_data *core,
		  काष्ठा hdmi_wp_data *wp);
व्योम hdmi4_cec_uninit(काष्ठा hdmi_core_data *core);
#अन्यथा
अटल अंतरभूत व्योम hdmi4_cec_set_phys_addr(काष्ठा hdmi_core_data *core, u16 pa)
अणु
पूर्ण

अटल अंतरभूत व्योम hdmi4_cec_irq(काष्ठा hdmi_core_data *core)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक hdmi4_cec_init(काष्ठा platक्रमm_device *pdev,
				काष्ठा hdmi_core_data *core,
				काष्ठा hdmi_wp_data *wp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hdmi4_cec_uninit(काष्ठा hdmi_core_data *core)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
