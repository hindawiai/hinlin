<शैली गुरु>
/*
 * vga_चयनeroo.h - Support क्रम laptop with dual GPU using one set of outमाला_दो
 *
 * Copyright (c) 2010 Red Hat Inc.
 * Author : Dave Airlie <airlied@redhat.com>
 *
 * Copyright (c) 2015 Lukas Wunner <lukas@wunner.de>
 *
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS
 * IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _LINUX_VGA_SWITCHEROO_H_
#घोषणा _LINUX_VGA_SWITCHEROO_H_

#समावेश <linux/fb.h>

काष्ठा pci_dev;

/**
 * क्रमागत vga_चयनeroo_handler_flags_t - handler flags biपंचांगask
 * @VGA_SWITCHEROO_CAN_SWITCH_DDC: whether the handler is able to चयन the
 * 	DDC lines separately. This संकेतs to clients that they should call
 * 	drm_get_edid_चयनeroo() to probe the EDID
 * @VGA_SWITCHEROO_NEEDS_EDP_CONFIG: whether the handler is unable to चयन
 * 	the AUX channel separately. This संकेतs to clients that the active
 * 	GPU needs to train the link and communicate the link parameters to the
 * 	inactive GPU (mediated by vga_चयनeroo). The inactive GPU may then
 * 	skip the AUX handshake and set up its output with these pre-calibrated
 * 	values (DisplayPort specअगरication v1.1a, section 2.5.3.3)
 *
 * Handler flags biपंचांगask. Used by handlers to declare their capabilities upon
 * रेजिस्टरing with vga_चयनeroo.
 */
क्रमागत vga_चयनeroo_handler_flags_t अणु
	VGA_SWITCHEROO_CAN_SWITCH_DDC	= (1 << 0),
	VGA_SWITCHEROO_NEEDS_EDP_CONFIG	= (1 << 1),
पूर्ण;

/**
 * क्रमागत vga_चयनeroo_state - client घातer state
 * @VGA_SWITCHEROO_OFF: off
 * @VGA_SWITCHEROO_ON: on
 * @VGA_SWITCHEROO_NOT_FOUND: client has not रेजिस्टरed with vga_चयनeroo.
 * 	Only used in vga_चयनeroo_get_client_state() which in turn is only
 * 	called from hda_पूर्णांकel.c
 *
 * Client घातer state.
 */
क्रमागत vga_चयनeroo_state अणु
	VGA_SWITCHEROO_OFF,
	VGA_SWITCHEROO_ON,
	/* below are referred only from vga_चयनeroo_get_client_state() */
	VGA_SWITCHEROO_NOT_FOUND,
पूर्ण;

/**
 * क्रमागत vga_चयनeroo_client_id - client identअगरier
 * @VGA_SWITCHEROO_UNKNOWN_ID: initial identअगरier asचिन्हित to vga clients.
 * 	Determining the id requires the handler, so GPUs are given their
 * 	true id in a delayed fashion in vga_चयनeroo_enable()
 * @VGA_SWITCHEROO_IGD: पूर्णांकegrated graphics device
 * @VGA_SWITCHEROO_DIS: discrete graphics device
 * @VGA_SWITCHEROO_MAX_CLIENTS: currently no more than two GPUs are supported
 *
 * Client identअगरier. Audio clients use the same identअगरier & 0x100.
 */
क्रमागत vga_चयनeroo_client_id अणु
	VGA_SWITCHEROO_UNKNOWN_ID = 0x1000,
	VGA_SWITCHEROO_IGD = 0,
	VGA_SWITCHEROO_DIS,
	VGA_SWITCHEROO_MAX_CLIENTS,
पूर्ण;

/**
 * काष्ठा vga_चयनeroo_handler - handler callbacks
 * @init: initialize handler.
 * 	Optional. This माला_लो called when vga_चयनeroo is enabled, i.e. when
 * 	two vga clients have रेजिस्टरed. It allows the handler to perक्रमm
 * 	some delayed initialization that depends on the existence of the
 * 	vga clients. Currently only the radeon and amdgpu drivers use this.
 * 	The वापस value is ignored
 * @चयनto: चयन outमाला_दो to given client.
 * 	Mandatory. For muxless machines this should be a no-op. Returning 0
 * 	denotes success, anything अन्यथा failure (in which हाल the चयन is
 * 	पातed)
 * @चयन_ddc: चयन DDC lines to given client.
 * 	Optional. Should वापस the previous DDC owner on success or a
 * 	negative पूर्णांक on failure
 * @घातer_state: cut or reinstate घातer of given client.
 * 	Optional. The वापस value is ignored
 * @get_client_id: determine अगर given pci device is पूर्णांकegrated or discrete GPU.
 * 	Mandatory
 *
 * Handler callbacks. The multiplexer itself. The @चयनto and @get_client_id
 * methods are mandatory, all others may be set to शून्य.
 */
काष्ठा vga_चयनeroo_handler अणु
	पूर्णांक (*init)(व्योम);
	पूर्णांक (*चयनto)(क्रमागत vga_चयनeroo_client_id id);
	पूर्णांक (*चयन_ddc)(क्रमागत vga_चयनeroo_client_id id);
	पूर्णांक (*घातer_state)(क्रमागत vga_चयनeroo_client_id id,
			   क्रमागत vga_चयनeroo_state state);
	क्रमागत vga_चयनeroo_client_id (*get_client_id)(काष्ठा pci_dev *pdev);
पूर्ण;

/**
 * काष्ठा vga_चयनeroo_client_ops - client callbacks
 * @set_gpu_state: करो the equivalent of suspend/resume क्रम the card.
 * 	Mandatory. This should not cut घातer to the discrete GPU,
 * 	which is the job of the handler
 * @reprobe: poll outमाला_दो.
 * 	Optional. This माला_लो called after waking the GPU and चयनing
 * 	the outमाला_दो to it
 * @can_चयन: check अगर the device is in a position to चयन now.
 * 	Mandatory. The client should वापस false अगर a user space process
 * 	has one of its device files खोलो
 * @gpu_bound: notअगरy the client id to audio client when the GPU is bound.
 *
 * Client callbacks. A client can be either a GPU or an audio device on a GPU.
 * The @set_gpu_state and @can_चयन methods are mandatory, @reprobe may be
 * set to शून्य. For audio clients, the @reprobe member is bogus.
 * OTOH, @gpu_bound is only क्रम audio clients, and not used क्रम GPU clients.
 */
काष्ठा vga_चयनeroo_client_ops अणु
	व्योम (*set_gpu_state)(काष्ठा pci_dev *dev, क्रमागत vga_चयनeroo_state);
	व्योम (*reprobe)(काष्ठा pci_dev *dev);
	bool (*can_चयन)(काष्ठा pci_dev *dev);
	व्योम (*gpu_bound)(काष्ठा pci_dev *dev, क्रमागत vga_चयनeroo_client_id);
पूर्ण;

#अगर defined(CONFIG_VGA_SWITCHEROO)
व्योम vga_चयनeroo_unरेजिस्टर_client(काष्ठा pci_dev *dev);
पूर्णांक vga_चयनeroo_रेजिस्टर_client(काष्ठा pci_dev *dev,
				   स्थिर काष्ठा vga_चयनeroo_client_ops *ops,
				   bool driver_घातer_control);
पूर्णांक vga_चयनeroo_रेजिस्टर_audio_client(काष्ठा pci_dev *pdev,
					 स्थिर काष्ठा vga_चयनeroo_client_ops *ops,
					 काष्ठा pci_dev *vga_dev);

व्योम vga_चयनeroo_client_fb_set(काष्ठा pci_dev *dev,
				  काष्ठा fb_info *info);

पूर्णांक vga_चयनeroo_रेजिस्टर_handler(स्थिर काष्ठा vga_चयनeroo_handler *handler,
				    क्रमागत vga_चयनeroo_handler_flags_t handler_flags);
व्योम vga_चयनeroo_unरेजिस्टर_handler(व्योम);
क्रमागत vga_चयनeroo_handler_flags_t vga_चयनeroo_handler_flags(व्योम);
पूर्णांक vga_चयनeroo_lock_ddc(काष्ठा pci_dev *pdev);
पूर्णांक vga_चयनeroo_unlock_ddc(काष्ठा pci_dev *pdev);

पूर्णांक vga_चयनeroo_process_delayed_चयन(व्योम);

bool vga_चयनeroo_client_probe_defer(काष्ठा pci_dev *pdev);
क्रमागत vga_चयनeroo_state vga_चयनeroo_get_client_state(काष्ठा pci_dev *dev);

पूर्णांक vga_चयनeroo_init_करोमुख्य_pm_ops(काष्ठा device *dev, काष्ठा dev_pm_करोमुख्य *करोमुख्य);
व्योम vga_चयनeroo_fini_करोमुख्य_pm_ops(काष्ठा device *dev);
#अन्यथा

अटल अंतरभूत व्योम vga_चयनeroo_unरेजिस्टर_client(काष्ठा pci_dev *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक vga_चयनeroo_रेजिस्टर_client(काष्ठा pci_dev *dev,
		स्थिर काष्ठा vga_चयनeroo_client_ops *ops, bool driver_घातer_control) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vga_चयनeroo_client_fb_set(काष्ठा pci_dev *dev, काष्ठा fb_info *info) अणुपूर्ण
अटल अंतरभूत पूर्णांक vga_चयनeroo_रेजिस्टर_handler(स्थिर काष्ठा vga_चयनeroo_handler *handler,
		क्रमागत vga_चयनeroo_handler_flags_t handler_flags) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक vga_चयनeroo_रेजिस्टर_audio_client(काष्ठा pci_dev *pdev,
	स्थिर काष्ठा vga_चयनeroo_client_ops *ops,
	काष्ठा pci_dev *vga_dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vga_चयनeroo_unरेजिस्टर_handler(व्योम) अणुपूर्ण
अटल अंतरभूत क्रमागत vga_चयनeroo_handler_flags_t vga_चयनeroo_handler_flags(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक vga_चयनeroo_lock_ddc(काष्ठा pci_dev *pdev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक vga_चयनeroo_unlock_ddc(काष्ठा pci_dev *pdev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक vga_चयनeroo_process_delayed_चयन(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत bool vga_चयनeroo_client_probe_defer(काष्ठा pci_dev *pdev) अणु वापस false; पूर्ण
अटल अंतरभूत क्रमागत vga_चयनeroo_state vga_चयनeroo_get_client_state(काष्ठा pci_dev *dev) अणु वापस VGA_SWITCHEROO_ON; पूर्ण

अटल अंतरभूत पूर्णांक vga_चयनeroo_init_करोमुख्य_pm_ops(काष्ठा device *dev, काष्ठा dev_pm_करोमुख्य *करोमुख्य) अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत व्योम vga_चयनeroo_fini_करोमुख्य_pm_ops(काष्ठा device *dev) अणुपूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* _LINUX_VGA_SWITCHEROO_H_ */
