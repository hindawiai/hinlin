<शैली गुरु>
/*
 * vga_चयनeroo.c - Support क्रम laptop with dual GPU using one set of outमाला_दो
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

#घोषणा pr_fmt(fmt) "vga_switcheroo: " fmt

#समावेश <linux/apple-gmux.h>
#समावेश <linux/console.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fb.h>
#समावेश <linux/fs.h>
#समावेश <linux/fbcon.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vgaarb.h>
#समावेश <linux/vga_चयनeroo.h>

/**
 * DOC: Overview
 *
 * vga_चयनeroo is the Linux subप्रणाली क्रम laptop hybrid graphics.
 * These come in two flavors:
 *
 * * muxed: Dual GPUs with a multiplexer chip to चयन outमाला_दो between GPUs.
 * * muxless: Dual GPUs but only one of them is connected to outमाला_दो.
 *   The other one is merely used to offload rendering, its results
 *   are copied over PCIe पूर्णांकo the framebuffer. On Linux this is
 *   supported with DRI PRIME.
 *
 * Hybrid graphics started to appear in the late Naughties and were initially
 * all muxed. Newer laptops moved to a muxless architecture क्रम cost reasons.
 * A notable exception is the MacBook Pro which जारीs to use a mux.
 * Muxes come with varying capabilities: Some चयन only the panel, others
 * can also चयन बाह्यal displays. Some चयन all display pins at once
 * जबतक others can चयन just the DDC lines. (To allow EDID probing
 * क्रम the inactive GPU.) Also, muxes are often used to cut घातer to the
 * discrete GPU जबतक it is not used.
 *
 * DRM drivers रेजिस्टर GPUs with vga_चयनeroo, these are henceक्रमth called
 * clients. The mux is called the handler. Muxless machines also रेजिस्टर a
 * handler to control the घातer state of the discrete GPU, its ->चयनto
 * callback is a no-op क्रम obvious reasons. The discrete GPU is often equipped
 * with an HDA controller क्रम the HDMI/DP audio संकेत, this will also
 * रेजिस्टर as a client so that vga_चयनeroo can take care of the correct
 * suspend/resume order when changing the discrete GPU's घातer state. In total
 * there can thus be up to three clients: Two vga clients (GPUs) and one audio
 * client (on the discrete GPU). The code is mostly prepared to support
 * machines with more than two GPUs should they become available.
 *
 * The GPU to which the outमाला_दो are currently चयनed is called the
 * active client in vga_चयनeroo parlance. The GPU not in use is the
 * inactive client. When the inactive client's DRM driver is loaded,
 * it will be unable to probe the panel's EDID and hence depends on
 * VBIOS to provide its display modes. If the VBIOS modes are bogus or
 * अगर there is no VBIOS at all (which is common on the MacBook Pro),
 * a client may alternatively request that the DDC lines are temporarily
 * चयनed to it, provided that the handler supports this. Switching
 * only the DDC lines and not the entire output aव्योमs unnecessary
 * flickering.
 */

/**
 * काष्ठा vga_चयनeroo_client - रेजिस्टरed client
 * @pdev: client pci device
 * @fb_info: framebuffer to which console is remapped on चयनing
 * @pwr_state: current घातer state अगर manual घातer control is used.
 *	For driver घातer control, call vga_चयनeroo_pwr_state().
 * @ops: client callbacks
 * @id: client identअगरier. Determining the id requires the handler,
 *	so gpus are initially asचिन्हित VGA_SWITCHEROO_UNKNOWN_ID
 *	and later given their true id in vga_चयनeroo_enable()
 * @active: whether the outमाला_दो are currently चयनed to this client
 * @driver_घातer_control: whether घातer state is controlled by the driver's
 *	runसमय pm. If true, writing ON and OFF to the vga_चयनeroo debugfs
 *	पूर्णांकerface is a no-op so as not to पूर्णांकerfere with runसमय pm
 * @list: client list
 * @vga_dev: pci device, indicate which GPU is bound to current audio client
 *
 * Registered client. A client can be either a GPU or an audio device on a GPU.
 * For audio clients, the @fb_info and @active members are bogus. For GPU
 * clients, the @vga_dev is bogus.
 */
काष्ठा vga_चयनeroo_client अणु
	काष्ठा pci_dev *pdev;
	काष्ठा fb_info *fb_info;
	क्रमागत vga_चयनeroo_state pwr_state;
	स्थिर काष्ठा vga_चयनeroo_client_ops *ops;
	क्रमागत vga_चयनeroo_client_id id;
	bool active;
	bool driver_घातer_control;
	काष्ठा list_head list;
	काष्ठा pci_dev *vga_dev;
पूर्ण;

/*
 * protects access to काष्ठा vgasr_priv
 */
अटल DEFINE_MUTEX(vgasr_mutex);

/**
 * काष्ठा vgasr_priv - vga_चयनeroo निजी data
 * @active: whether vga_चयनeroo is enabled.
 *	Prerequisite is the registration of two GPUs and a handler
 * @delayed_चयन_active: whether a delayed चयन is pending
 * @delayed_client_id: client to which a delayed चयन is pending
 * @debugfs_root: directory क्रम vga_चयनeroo debugfs पूर्णांकerface
 * @रेजिस्टरed_clients: number of रेजिस्टरed GPUs
 *	(counting only vga clients, not audio clients)
 * @clients: list of रेजिस्टरed clients
 * @handler: रेजिस्टरed handler
 * @handler_flags: flags of रेजिस्टरed handler
 * @mux_hw_lock: protects mux state
 *	(in particular जबतक DDC lines are temporarily चयनed)
 * @old_ddc_owner: client to which DDC lines will be चयनed back on unlock
 *
 * vga_चयनeroo निजी data. Currently only one vga_चयनeroo instance
 * per प्रणाली is supported.
 */
काष्ठा vgasr_priv अणु
	bool active;
	bool delayed_चयन_active;
	क्रमागत vga_चयनeroo_client_id delayed_client_id;

	काष्ठा dentry *debugfs_root;

	पूर्णांक रेजिस्टरed_clients;
	काष्ठा list_head clients;

	स्थिर काष्ठा vga_चयनeroo_handler *handler;
	क्रमागत vga_चयनeroo_handler_flags_t handler_flags;
	काष्ठा mutex mux_hw_lock;
	पूर्णांक old_ddc_owner;
पूर्ण;

#घोषणा ID_BIT_AUDIO		0x100
#घोषणा client_is_audio(c)		((c)->id & ID_BIT_AUDIO)
#घोषणा client_is_vga(c)		(!client_is_audio(c))
#घोषणा client_id(c)		((c)->id & ~ID_BIT_AUDIO)

अटल व्योम vga_चयनeroo_debugfs_init(काष्ठा vgasr_priv *priv);
अटल व्योम vga_चयनeroo_debugfs_fini(काष्ठा vgasr_priv *priv);

/* only one चयनeroo per प्रणाली */
अटल काष्ठा vgasr_priv vgasr_priv = अणु
	.clients = LIST_HEAD_INIT(vgasr_priv.clients),
	.mux_hw_lock = __MUTEX_INITIALIZER(vgasr_priv.mux_hw_lock),
पूर्ण;

अटल bool vga_चयनeroo_पढ़ोy(व्योम)
अणु
	/* we're पढ़ोy अगर we get two clients + handler */
	वापस !vgasr_priv.active &&
	       vgasr_priv.रेजिस्टरed_clients == 2 && vgasr_priv.handler;
पूर्ण

अटल व्योम vga_चयनeroo_enable(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा vga_चयनeroo_client *client;

	/* call the handler to init */
	अगर (vgasr_priv.handler->init)
		vgasr_priv.handler->init();

	list_क्रम_each_entry(client, &vgasr_priv.clients, list) अणु
		अगर (!client_is_vga(client) ||
		     client_id(client) != VGA_SWITCHEROO_UNKNOWN_ID)
			जारी;

		ret = vgasr_priv.handler->get_client_id(client->pdev);
		अगर (ret < 0)
			वापस;

		client->id = ret;
	पूर्ण

	list_क्रम_each_entry(client, &vgasr_priv.clients, list) अणु
		अगर (!client_is_audio(client) ||
		     client_id(client) != VGA_SWITCHEROO_UNKNOWN_ID)
			जारी;

		ret = vgasr_priv.handler->get_client_id(client->vga_dev);
		अगर (ret < 0)
			वापस;

		client->id = ret | ID_BIT_AUDIO;
		अगर (client->ops->gpu_bound)
			client->ops->gpu_bound(client->pdev, ret);
	पूर्ण

	vga_चयनeroo_debugfs_init(&vgasr_priv);
	vgasr_priv.active = true;
पूर्ण

/**
 * vga_चयनeroo_रेजिस्टर_handler() - रेजिस्टर handler
 * @handler: handler callbacks
 * @handler_flags: handler flags
 *
 * Register handler. Enable vga_चयनeroo अगर two vga clients have alपढ़ोy
 * रेजिस्टरed.
 *
 * Return: 0 on success, -EINVAL अगर a handler was alपढ़ोy रेजिस्टरed.
 */
पूर्णांक vga_चयनeroo_रेजिस्टर_handler(
			  स्थिर काष्ठा vga_चयनeroo_handler *handler,
			  क्रमागत vga_चयनeroo_handler_flags_t handler_flags)
अणु
	mutex_lock(&vgasr_mutex);
	अगर (vgasr_priv.handler) अणु
		mutex_unlock(&vgasr_mutex);
		वापस -EINVAL;
	पूर्ण

	vgasr_priv.handler = handler;
	vgasr_priv.handler_flags = handler_flags;
	अगर (vga_चयनeroo_पढ़ोy()) अणु
		pr_info("enabled\n");
		vga_चयनeroo_enable();
	पूर्ण
	mutex_unlock(&vgasr_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_रेजिस्टर_handler);

/**
 * vga_चयनeroo_unरेजिस्टर_handler() - unरेजिस्टर handler
 *
 * Unरेजिस्टर handler. Disable vga_चयनeroo.
 */
व्योम vga_चयनeroo_unरेजिस्टर_handler(व्योम)
अणु
	mutex_lock(&vgasr_mutex);
	mutex_lock(&vgasr_priv.mux_hw_lock);
	vgasr_priv.handler_flags = 0;
	vgasr_priv.handler = शून्य;
	अगर (vgasr_priv.active) अणु
		pr_info("disabled\n");
		vga_चयनeroo_debugfs_fini(&vgasr_priv);
		vgasr_priv.active = false;
	पूर्ण
	mutex_unlock(&vgasr_priv.mux_hw_lock);
	mutex_unlock(&vgasr_mutex);
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_unरेजिस्टर_handler);

/**
 * vga_चयनeroo_handler_flags() - obtain handler flags
 *
 * Helper क्रम clients to obtain the handler flags biपंचांगask.
 *
 * Return: Handler flags. A value of 0 means that no handler is रेजिस्टरed
 * or that the handler has no special capabilities.
 */
क्रमागत vga_चयनeroo_handler_flags_t vga_चयनeroo_handler_flags(व्योम)
अणु
	वापस vgasr_priv.handler_flags;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_handler_flags);

अटल पूर्णांक रेजिस्टर_client(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा vga_चयनeroo_client_ops *ops,
			   क्रमागत vga_चयनeroo_client_id id,
			   काष्ठा pci_dev *vga_dev,
			   bool active,
			   bool driver_घातer_control)
अणु
	काष्ठा vga_चयनeroo_client *client;

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस -ENOMEM;

	client->pwr_state = VGA_SWITCHEROO_ON;
	client->pdev = pdev;
	client->ops = ops;
	client->id = id;
	client->active = active;
	client->driver_घातer_control = driver_घातer_control;
	client->vga_dev = vga_dev;

	mutex_lock(&vgasr_mutex);
	list_add_tail(&client->list, &vgasr_priv.clients);
	अगर (client_is_vga(client))
		vgasr_priv.रेजिस्टरed_clients++;

	अगर (vga_चयनeroo_पढ़ोy()) अणु
		pr_info("enabled\n");
		vga_चयनeroo_enable();
	पूर्ण
	mutex_unlock(&vgasr_mutex);
	वापस 0;
पूर्ण

/**
 * vga_चयनeroo_रेजिस्टर_client - रेजिस्टर vga client
 * @pdev: client pci device
 * @ops: client callbacks
 * @driver_घातer_control: whether घातer state is controlled by the driver's
 *	runसमय pm
 *
 * Register vga client (GPU). Enable vga_चयनeroo अगर another GPU and a
 * handler have alपढ़ोy रेजिस्टरed. The घातer state of the client is assumed
 * to be ON. Beक्रमehand, vga_चयनeroo_client_probe_defer() shall be called
 * to ensure that all prerequisites are met.
 *
 * Return: 0 on success, -ENOMEM on memory allocation error.
 */
पूर्णांक vga_चयनeroo_रेजिस्टर_client(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा vga_चयनeroo_client_ops *ops,
				   bool driver_घातer_control)
अणु
	वापस रेजिस्टर_client(pdev, ops, VGA_SWITCHEROO_UNKNOWN_ID, शून्य,
			       pdev == vga_शेष_device(),
			       driver_घातer_control);
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_रेजिस्टर_client);

/**
 * vga_चयनeroo_रेजिस्टर_audio_client - रेजिस्टर audio client
 * @pdev: client pci device
 * @ops: client callbacks
 * @vga_dev:  pci device which is bound to current audio client
 *
 * Register audio client (audio device on a GPU). The client is assumed
 * to use runसमय PM. Beक्रमehand, vga_चयनeroo_client_probe_defer()
 * shall be called to ensure that all prerequisites are met.
 *
 * Return: 0 on success, -ENOMEM on memory allocation error, -EINVAL on getting
 * client id error.
 */
पूर्णांक vga_चयनeroo_रेजिस्टर_audio_client(काष्ठा pci_dev *pdev,
			स्थिर काष्ठा vga_चयनeroo_client_ops *ops,
			काष्ठा pci_dev *vga_dev)
अणु
	क्रमागत vga_चयनeroo_client_id id = VGA_SWITCHEROO_UNKNOWN_ID;

	/*
	 * अगर vga_चयनeroo has enabled, that mean two GPU clients and also
	 * handler are रेजिस्टरed. Get audio client id from bound GPU client
	 * id directly, otherwise, set it as VGA_SWITCHEROO_UNKNOWN_ID,
	 * it will set to correct id in later when vga_चयनeroo_enable()
	 * is called.
	 */
	mutex_lock(&vgasr_mutex);
	अगर (vgasr_priv.active) अणु
		id = vgasr_priv.handler->get_client_id(vga_dev);
		अगर (id < 0) अणु
			mutex_unlock(&vgasr_mutex);
			वापस -EINVAL;
		पूर्ण
		/* notअगरy अगर GPU has been alपढ़ोy bound */
		अगर (ops->gpu_bound)
			ops->gpu_bound(pdev, id);
	पूर्ण
	mutex_unlock(&vgasr_mutex);

	वापस रेजिस्टर_client(pdev, ops, id | ID_BIT_AUDIO, vga_dev,
			       false, true);
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_रेजिस्टर_audio_client);

अटल काष्ठा vga_चयनeroo_client *
find_client_from_pci(काष्ठा list_head *head, काष्ठा pci_dev *pdev)
अणु
	काष्ठा vga_चयनeroo_client *client;

	list_क्रम_each_entry(client, head, list)
		अगर (client->pdev == pdev)
			वापस client;
	वापस शून्य;
पूर्ण

अटल काष्ठा vga_चयनeroo_client *
find_client_from_id(काष्ठा list_head *head,
		    क्रमागत vga_चयनeroo_client_id client_id)
अणु
	काष्ठा vga_चयनeroo_client *client;

	list_क्रम_each_entry(client, head, list)
		अगर (client->id == client_id)
			वापस client;
	वापस शून्य;
पूर्ण

अटल काष्ठा vga_चयनeroo_client *
find_active_client(काष्ठा list_head *head)
अणु
	काष्ठा vga_चयनeroo_client *client;

	list_क्रम_each_entry(client, head, list)
		अगर (client->active)
			वापस client;
	वापस शून्य;
पूर्ण

/**
 * vga_चयनeroo_client_probe_defer() - whether to defer probing a given client
 * @pdev: client pci device
 *
 * Determine whether any prerequisites are not fulfilled to probe a given
 * client. Drivers shall invoke this early on in their ->probe callback
 * and वापस %-EPROBE_DEFER अगर it evaluates to %true. Thou shalt not
 * रेजिस्टर the client ere thou hast called this.
 *
 * Return: %true अगर probing should be deferred, otherwise %false.
 */
bool vga_चयनeroo_client_probe_defer(काष्ठा pci_dev *pdev)
अणु
	अगर ((pdev->class >> 16) == PCI_BASE_CLASS_DISPLAY) अणु
		/*
		 * apple-gmux is needed on pre-retina MacBook Pro
		 * to probe the panel अगर pdev is the inactive GPU.
		 */
		अगर (apple_gmux_present() && pdev != vga_शेष_device() &&
		    !vgasr_priv.handler_flags)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_client_probe_defer);

अटल क्रमागत vga_चयनeroo_state
vga_चयनeroo_pwr_state(काष्ठा vga_चयनeroo_client *client)
अणु
	अगर (client->driver_घातer_control)
		अगर (pm_runसमय_enabled(&client->pdev->dev) &&
		    pm_runसमय_active(&client->pdev->dev))
			वापस VGA_SWITCHEROO_ON;
		अन्यथा
			वापस VGA_SWITCHEROO_OFF;
	अन्यथा
		वापस client->pwr_state;
पूर्ण

/**
 * vga_चयनeroo_get_client_state() - obtain घातer state of a given client
 * @pdev: client pci device
 *
 * Obtain घातer state of a given client as seen from vga_चयनeroo.
 * The function is only called from hda_पूर्णांकel.c.
 *
 * Return: Power state.
 */
क्रमागत vga_चयनeroo_state vga_चयनeroo_get_client_state(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vga_चयनeroo_client *client;
	क्रमागत vga_चयनeroo_state ret;

	mutex_lock(&vgasr_mutex);
	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	अगर (!client)
		ret = VGA_SWITCHEROO_NOT_FOUND;
	अन्यथा
		ret = vga_चयनeroo_pwr_state(client);
	mutex_unlock(&vgasr_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_get_client_state);

/**
 * vga_चयनeroo_unरेजिस्टर_client() - unरेजिस्टर client
 * @pdev: client pci device
 *
 * Unरेजिस्टर client. Disable vga_चयनeroo अगर this is a vga client (GPU).
 */
व्योम vga_चयनeroo_unरेजिस्टर_client(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vga_चयनeroo_client *client;

	mutex_lock(&vgasr_mutex);
	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	अगर (client) अणु
		अगर (client_is_vga(client))
			vgasr_priv.रेजिस्टरed_clients--;
		list_del(&client->list);
		kमुक्त(client);
	पूर्ण
	अगर (vgasr_priv.active && vgasr_priv.रेजिस्टरed_clients < 2) अणु
		pr_info("disabled\n");
		vga_चयनeroo_debugfs_fini(&vgasr_priv);
		vgasr_priv.active = false;
	पूर्ण
	mutex_unlock(&vgasr_mutex);
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_unरेजिस्टर_client);

/**
 * vga_चयनeroo_client_fb_set() - set framebuffer of a given client
 * @pdev: client pci device
 * @info: framebuffer
 *
 * Set framebuffer of a given client. The console will be remapped to this
 * on चयनing.
 */
व्योम vga_चयनeroo_client_fb_set(काष्ठा pci_dev *pdev,
				 काष्ठा fb_info *info)
अणु
	काष्ठा vga_चयनeroo_client *client;

	mutex_lock(&vgasr_mutex);
	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	अगर (client)
		client->fb_info = info;
	mutex_unlock(&vgasr_mutex);
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_client_fb_set);

/**
 * vga_चयनeroo_lock_ddc() - temporarily चयन DDC lines to a given client
 * @pdev: client pci device
 *
 * Temporarily चयन DDC lines to the client identअगरied by @pdev
 * (but leave the outमाला_दो otherwise चयनed to where they are).
 * This allows the inactive client to probe EDID. The DDC lines must
 * afterwards be चयनed back by calling vga_चयनeroo_unlock_ddc(),
 * even अगर this function वापसs an error.
 *
 * Return: Previous DDC owner on success or a negative पूर्णांक on error.
 * Specअगरically, %-ENODEV अगर no handler has रेजिस्टरed or अगर the handler
 * करोes not support चयनing the DDC lines. Also, a negative value
 * वापसed by the handler is propagated back to the caller.
 * The वापस value has merely an inक्रमmational purpose क्रम any caller
 * which might be पूर्णांकerested in it. It is acceptable to ignore the वापस
 * value and simply rely on the result of the subsequent EDID probe,
 * which will be %शून्य अगर DDC चयनing failed.
 */
पूर्णांक vga_चयनeroo_lock_ddc(काष्ठा pci_dev *pdev)
अणु
	क्रमागत vga_चयनeroo_client_id id;

	mutex_lock(&vgasr_priv.mux_hw_lock);
	अगर (!vgasr_priv.handler || !vgasr_priv.handler->चयन_ddc) अणु
		vgasr_priv.old_ddc_owner = -ENODEV;
		वापस -ENODEV;
	पूर्ण

	id = vgasr_priv.handler->get_client_id(pdev);
	vgasr_priv.old_ddc_owner = vgasr_priv.handler->चयन_ddc(id);
	वापस vgasr_priv.old_ddc_owner;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_lock_ddc);

/**
 * vga_चयनeroo_unlock_ddc() - चयन DDC lines back to previous owner
 * @pdev: client pci device
 *
 * Switch DDC lines back to the previous owner after calling
 * vga_चयनeroo_lock_ddc(). This must be called even अगर
 * vga_चयनeroo_lock_ddc() वापसed an error.
 *
 * Return: Previous DDC owner on success (i.e. the client identअगरier of @pdev)
 * or a negative पूर्णांक on error.
 * Specअगरically, %-ENODEV अगर no handler has रेजिस्टरed or अगर the handler
 * करोes not support चयनing the DDC lines. Also, a negative value
 * वापसed by the handler is propagated back to the caller.
 * Finally, invoking this function without calling vga_चयनeroo_lock_ddc()
 * first is not allowed and will result in %-EINVAL.
 */
पूर्णांक vga_चयनeroo_unlock_ddc(काष्ठा pci_dev *pdev)
अणु
	क्रमागत vga_चयनeroo_client_id id;
	पूर्णांक ret = vgasr_priv.old_ddc_owner;

	अगर (WARN_ON_ONCE(!mutex_is_locked(&vgasr_priv.mux_hw_lock)))
		वापस -EINVAL;

	अगर (vgasr_priv.old_ddc_owner >= 0) अणु
		id = vgasr_priv.handler->get_client_id(pdev);
		अगर (vgasr_priv.old_ddc_owner != id)
			ret = vgasr_priv.handler->चयन_ddc(
						     vgasr_priv.old_ddc_owner);
	पूर्ण
	mutex_unlock(&vgasr_priv.mux_hw_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_unlock_ddc);

/**
 * DOC: Manual चयनing and manual घातer control
 *
 * In this mode of use, the file /sys/kernel/debug/vgaचयनeroo/चयन
 * can be पढ़ो to retrieve the current vga_चयनeroo state and commands
 * can be written to it to change the state. The file appears as soon as
 * two GPU drivers and one handler have रेजिस्टरed with vga_चयनeroo.
 * The following commands are understood:
 *
 * * OFF: Power off the device not in use.
 * * ON: Power on the device not in use.
 * * IGD: Switch to the पूर्णांकegrated graphics device.
 *   Power on the पूर्णांकegrated GPU अगर necessary, घातer off the discrete GPU.
 *   Prerequisite is that no user space processes (e.g. Xorg, alsactl)
 *   have खोलोed device files of the GPUs or the audio client. If the
 *   चयन fails, the user may invoke lsof(8) or fuser(1) on /dev/dri/
 *   and /dev/snd/controlC1 to identअगरy processes blocking the चयन.
 * * DIS: Switch to the discrete graphics device.
 * * DIGD: Delayed चयन to the पूर्णांकegrated graphics device.
 *   This will perक्रमm the चयन once the last user space process has
 *   बंदd the device files of the GPUs and the audio client.
 * * DDIS: Delayed चयन to the discrete graphics device.
 * * MIGD: Mux-only चयन to the पूर्णांकegrated graphics device.
 *   Does not remap console or change the घातer state of either gpu.
 *   If the पूर्णांकegrated GPU is currently off, the screen will turn black.
 *   If it is on, the screen will show whatever happens to be in VRAM.
 *   Either way, the user has to blindly enter the command to चयन back.
 * * MDIS: Mux-only चयन to the discrete graphics device.
 *
 * For GPUs whose घातer state is controlled by the driver's runसमय pm,
 * the ON and OFF commands are a no-op (see next section).
 *
 * For muxless machines, the IGD/DIS, DIGD/DDIS and MIGD/MDIS commands
 * should not be used.
 */

अटल पूर्णांक vga_चयनeroo_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा vga_चयनeroo_client *client;
	पूर्णांक i = 0;

	mutex_lock(&vgasr_mutex);
	list_क्रम_each_entry(client, &vgasr_priv.clients, list) अणु
		seq_म_लिखो(m, "%d:%s%s:%c:%s%s:%s\n", i,
			   client_id(client) == VGA_SWITCHEROO_DIS ? "DIS" :
								     "IGD",
			   client_is_vga(client) ? "" : "-Audio",
			   client->active ? '+' : ' ',
			   client->driver_घातer_control ? "Dyn" : "",
			   vga_चयनeroo_pwr_state(client) ? "Pwr" : "Off",
			   pci_name(client->pdev));
		i++;
	पूर्ण
	mutex_unlock(&vgasr_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vga_चयनeroo_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, vga_चयनeroo_show, शून्य);
पूर्ण

अटल पूर्णांक vga_चयनon(काष्ठा vga_चयनeroo_client *client)
अणु
	अगर (client->driver_घातer_control)
		वापस 0;
	अगर (vgasr_priv.handler->घातer_state)
		vgasr_priv.handler->घातer_state(client->id, VGA_SWITCHEROO_ON);
	/* call the driver callback to turn on device */
	client->ops->set_gpu_state(client->pdev, VGA_SWITCHEROO_ON);
	client->pwr_state = VGA_SWITCHEROO_ON;
	वापस 0;
पूर्ण

अटल पूर्णांक vga_चयनoff(काष्ठा vga_चयनeroo_client *client)
अणु
	अगर (client->driver_घातer_control)
		वापस 0;
	/* call the driver callback to turn off device */
	client->ops->set_gpu_state(client->pdev, VGA_SWITCHEROO_OFF);
	अगर (vgasr_priv.handler->घातer_state)
		vgasr_priv.handler->घातer_state(client->id, VGA_SWITCHEROO_OFF);
	client->pwr_state = VGA_SWITCHEROO_OFF;
	वापस 0;
पूर्ण

अटल व्योम set_audio_state(क्रमागत vga_चयनeroo_client_id id,
			    क्रमागत vga_चयनeroo_state state)
अणु
	काष्ठा vga_चयनeroo_client *client;

	client = find_client_from_id(&vgasr_priv.clients, id | ID_BIT_AUDIO);
	अगर (client)
		client->ops->set_gpu_state(client->pdev, state);
पूर्ण

/* stage one happens beक्रमe delay */
अटल पूर्णांक vga_चयनto_stage1(काष्ठा vga_चयनeroo_client *new_client)
अणु
	काष्ठा vga_चयनeroo_client *active;

	active = find_active_client(&vgasr_priv.clients);
	अगर (!active)
		वापस 0;

	अगर (vga_चयनeroo_pwr_state(new_client) == VGA_SWITCHEROO_OFF)
		vga_चयनon(new_client);

	vga_set_शेष_device(new_client->pdev);
	वापस 0;
पूर्ण

/* post delay */
अटल पूर्णांक vga_चयनto_stage2(काष्ठा vga_चयनeroo_client *new_client)
अणु
	पूर्णांक ret;
	काष्ठा vga_चयनeroo_client *active;

	active = find_active_client(&vgasr_priv.clients);
	अगर (!active)
		वापस 0;

	active->active = false;

	/* let HDA controller स्वतःsuspend अगर GPU uses driver घातer control */
	अगर (!active->driver_घातer_control)
		set_audio_state(active->id, VGA_SWITCHEROO_OFF);

	अगर (new_client->fb_info)
		fbcon_remap_all(new_client->fb_info);

	mutex_lock(&vgasr_priv.mux_hw_lock);
	ret = vgasr_priv.handler->चयनto(new_client->id);
	mutex_unlock(&vgasr_priv.mux_hw_lock);
	अगर (ret)
		वापस ret;

	अगर (new_client->ops->reprobe)
		new_client->ops->reprobe(new_client->pdev);

	अगर (vga_चयनeroo_pwr_state(active) == VGA_SWITCHEROO_ON)
		vga_चयनoff(active);

	/* let HDA controller स्वतःresume अगर GPU uses driver घातer control */
	अगर (!new_client->driver_घातer_control)
		set_audio_state(new_client->id, VGA_SWITCHEROO_ON);

	new_client->active = true;
	वापस 0;
पूर्ण

अटल bool check_can_चयन(व्योम)
अणु
	काष्ठा vga_चयनeroo_client *client;

	list_क्रम_each_entry(client, &vgasr_priv.clients, list) अणु
		अगर (!client->ops->can_चयन(client->pdev)) अणु
			pr_err("client %x refused switch\n", client->id);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल sमाप_प्रकार
vga_चयनeroo_debugfs_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			     माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर usercmd[64];
	पूर्णांक ret;
	bool delay = false, can_चयन;
	bool just_mux = false;
	क्रमागत vga_चयनeroo_client_id client_id = VGA_SWITCHEROO_UNKNOWN_ID;
	काष्ठा vga_चयनeroo_client *client = शून्य;

	अगर (cnt > 63)
		cnt = 63;

	अगर (copy_from_user(usercmd, ubuf, cnt))
		वापस -EFAULT;

	mutex_lock(&vgasr_mutex);

	अगर (!vgasr_priv.active) अणु
		cnt = -EINVAL;
		जाओ out;
	पूर्ण

	/* pwr off the device not in use */
	अगर (म_भेदन(usercmd, "OFF", 3) == 0) अणु
		list_क्रम_each_entry(client, &vgasr_priv.clients, list) अणु
			अगर (client->active || client_is_audio(client))
				जारी;
			अगर (client->driver_घातer_control)
				जारी;
			set_audio_state(client->id, VGA_SWITCHEROO_OFF);
			अगर (client->pwr_state == VGA_SWITCHEROO_ON)
				vga_चयनoff(client);
		पूर्ण
		जाओ out;
	पूर्ण
	/* pwr on the device not in use */
	अगर (म_भेदन(usercmd, "ON", 2) == 0) अणु
		list_क्रम_each_entry(client, &vgasr_priv.clients, list) अणु
			अगर (client->active || client_is_audio(client))
				जारी;
			अगर (client->driver_घातer_control)
				जारी;
			अगर (client->pwr_state == VGA_SWITCHEROO_OFF)
				vga_चयनon(client);
			set_audio_state(client->id, VGA_SWITCHEROO_ON);
		पूर्ण
		जाओ out;
	पूर्ण

	/* request a delayed चयन - test can we चयन now */
	अगर (म_भेदन(usercmd, "DIGD", 4) == 0) अणु
		client_id = VGA_SWITCHEROO_IGD;
		delay = true;
	पूर्ण

	अगर (म_भेदन(usercmd, "DDIS", 4) == 0) अणु
		client_id = VGA_SWITCHEROO_DIS;
		delay = true;
	पूर्ण

	अगर (म_भेदन(usercmd, "IGD", 3) == 0)
		client_id = VGA_SWITCHEROO_IGD;

	अगर (म_भेदन(usercmd, "DIS", 3) == 0)
		client_id = VGA_SWITCHEROO_DIS;

	अगर (म_भेदन(usercmd, "MIGD", 4) == 0) अणु
		just_mux = true;
		client_id = VGA_SWITCHEROO_IGD;
	पूर्ण
	अगर (म_भेदन(usercmd, "MDIS", 4) == 0) अणु
		just_mux = true;
		client_id = VGA_SWITCHEROO_DIS;
	पूर्ण

	अगर (client_id == VGA_SWITCHEROO_UNKNOWN_ID)
		जाओ out;
	client = find_client_from_id(&vgasr_priv.clients, client_id);
	अगर (!client)
		जाओ out;

	vgasr_priv.delayed_चयन_active = false;

	अगर (just_mux) अणु
		mutex_lock(&vgasr_priv.mux_hw_lock);
		ret = vgasr_priv.handler->चयनto(client_id);
		mutex_unlock(&vgasr_priv.mux_hw_lock);
		जाओ out;
	पूर्ण

	अगर (client->active)
		जाओ out;

	/* okay we want a चयन - test अगर devices are willing to चयन */
	can_चयन = check_can_चयन();

	अगर (can_चयन == false && delay == false)
		जाओ out;

	अगर (can_चयन) अणु
		ret = vga_चयनto_stage1(client);
		अगर (ret)
			pr_err("switching failed stage 1 %d\n", ret);

		ret = vga_चयनto_stage2(client);
		अगर (ret)
			pr_err("switching failed stage 2 %d\n", ret);

	पूर्ण अन्यथा अणु
		pr_info("setting delayed switch to client %d\n", client->id);
		vgasr_priv.delayed_चयन_active = true;
		vgasr_priv.delayed_client_id = client_id;

		ret = vga_चयनto_stage1(client);
		अगर (ret)
			pr_err("delayed switching stage 1 failed %d\n", ret);
	पूर्ण

out:
	mutex_unlock(&vgasr_mutex);
	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations vga_चयनeroo_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = vga_चयनeroo_debugfs_खोलो,
	.ग_लिखो = vga_चयनeroo_debugfs_ग_लिखो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम vga_चयनeroo_debugfs_fini(काष्ठा vgasr_priv *priv)
अणु
	debugfs_हटाओ_recursive(priv->debugfs_root);
	priv->debugfs_root = शून्य;
पूर्ण

अटल व्योम vga_चयनeroo_debugfs_init(काष्ठा vgasr_priv *priv)
अणु
	/* alपढ़ोy initialised */
	अगर (priv->debugfs_root)
		वापस;

	priv->debugfs_root = debugfs_create_dir("vgaswitcheroo", शून्य);

	debugfs_create_file("switch", 0644, priv->debugfs_root, शून्य,
			    &vga_चयनeroo_debugfs_fops);
पूर्ण

/**
 * vga_चयनeroo_process_delayed_चयन() - helper क्रम delayed चयनing
 *
 * Process a delayed चयन अगर one is pending. DRM drivers should call this
 * from their ->lastबंद callback.
 *
 * Return: 0 on success. -EINVAL अगर no delayed चयन is pending, अगर the client
 * has unरेजिस्टरed in the meanसमय or अगर there are other clients blocking the
 * चयन. If the actual चयन fails, an error is reported and 0 is वापसed.
 */
पूर्णांक vga_चयनeroo_process_delayed_चयन(व्योम)
अणु
	काष्ठा vga_चयनeroo_client *client;
	पूर्णांक ret;
	पूर्णांक err = -EINVAL;

	mutex_lock(&vgasr_mutex);
	अगर (!vgasr_priv.delayed_चयन_active)
		जाओ err;

	pr_info("processing delayed switch to %d\n",
		vgasr_priv.delayed_client_id);

	client = find_client_from_id(&vgasr_priv.clients,
				     vgasr_priv.delayed_client_id);
	अगर (!client || !check_can_चयन())
		जाओ err;

	ret = vga_चयनto_stage2(client);
	अगर (ret)
		pr_err("delayed switching failed stage 2 %d\n", ret);

	vgasr_priv.delayed_चयन_active = false;
	err = 0;
err:
	mutex_unlock(&vgasr_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_process_delayed_चयन);

/**
 * DOC: Driver घातer control
 *
 * In this mode of use, the discrete GPU स्वतःmatically घातers up and करोwn at
 * the discretion of the driver's runसमय pm. On muxed machines, the user may
 * still influence the muxer state by way of the debugfs पूर्णांकerface, however
 * the ON and OFF commands become a no-op क्रम the discrete GPU.
 *
 * This mode is the शेष on Nvidia HybridPower/Optimus and ATI PowerXpress.
 * Specअगरying nouveau.runpm=0, radeon.runpm=0 or amdgpu.runpm=0 on the kernel
 * command line disables it.
 *
 * After the GPU has been suspended, the handler needs to be called to cut
 * घातer to the GPU. Likewise it needs to reinstate घातer beक्रमe the GPU
 * can resume. This is achieved by vga_चयनeroo_init_करोमुख्य_pm_ops(),
 * which augments the GPU's suspend/resume functions by the requisite
 * calls to the handler.
 *
 * When the audio device resumes, the GPU needs to be woken. This is achieved
 * by a PCI quirk which calls device_link_add() to declare a dependency on the
 * GPU. That way, the GPU is kept awake whenever and as दीर्घ as the audio
 * device is in use.
 *
 * On muxed machines, अगर the mux is initially चयनed to the discrete GPU,
 * the user ends up with a black screen when the GPU घातers करोwn after boot.
 * As a workaround, the mux is क्रमced to the पूर्णांकegrated GPU on runसमय suspend,
 * cf. https://bugs.मुक्तdesktop.org/show_bug.cgi?id=75917
 */

अटल व्योम vga_चयनeroo_घातer_चयन(काष्ठा pci_dev *pdev,
					क्रमागत vga_चयनeroo_state state)
अणु
	काष्ठा vga_चयनeroo_client *client;

	अगर (!vgasr_priv.handler->घातer_state)
		वापस;

	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	अगर (!client)
		वापस;

	अगर (!client->driver_घातer_control)
		वापस;

	vgasr_priv.handler->घातer_state(client->id, state);
पूर्ण

/* चयनeroo घातer करोमुख्य */
अटल पूर्णांक vga_चयनeroo_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक ret;

	ret = dev->bus->pm->runसमय_suspend(dev);
	अगर (ret)
		वापस ret;
	mutex_lock(&vgasr_mutex);
	अगर (vgasr_priv.handler->चयनto) अणु
		mutex_lock(&vgasr_priv.mux_hw_lock);
		vgasr_priv.handler->चयनto(VGA_SWITCHEROO_IGD);
		mutex_unlock(&vgasr_priv.mux_hw_lock);
	पूर्ण
	pci_bus_set_current_state(pdev->bus, PCI_D3cold);
	vga_चयनeroo_घातer_चयन(pdev, VGA_SWITCHEROO_OFF);
	mutex_unlock(&vgasr_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vga_चयनeroo_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	mutex_lock(&vgasr_mutex);
	vga_चयनeroo_घातer_चयन(pdev, VGA_SWITCHEROO_ON);
	mutex_unlock(&vgasr_mutex);
	pci_resume_bus(pdev->bus);
	वापस dev->bus->pm->runसमय_resume(dev);
पूर्ण

/**
 * vga_चयनeroo_init_करोमुख्य_pm_ops() - helper क्रम driver घातer control
 * @dev: vga client device
 * @करोमुख्य: घातer करोमुख्य
 *
 * Helper क्रम GPUs whose घातer state is controlled by the driver's runसमय pm.
 * After the GPU has been suspended, the handler needs to be called to cut
 * घातer to the GPU. Likewise it needs to reinstate घातer beक्रमe the GPU
 * can resume. To this end, this helper augments the suspend/resume functions
 * by the requisite calls to the handler. It needs only be called on platक्रमms
 * where the घातer चयन is separate to the device being घातered करोwn.
 */
पूर्णांक vga_चयनeroo_init_करोमुख्य_pm_ops(काष्ठा device *dev,
				      काष्ठा dev_pm_करोमुख्य *करोमुख्य)
अणु
	/* copy over all the bus versions */
	अगर (dev->bus && dev->bus->pm) अणु
		करोमुख्य->ops = *dev->bus->pm;
		करोमुख्य->ops.runसमय_suspend = vga_चयनeroo_runसमय_suspend;
		करोमुख्य->ops.runसमय_resume = vga_चयनeroo_runसमय_resume;

		dev_pm_करोमुख्य_set(dev, करोमुख्य);
		वापस 0;
	पूर्ण
	dev_pm_करोमुख्य_set(dev, शून्य);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_init_करोमुख्य_pm_ops);

व्योम vga_चयनeroo_fini_करोमुख्य_pm_ops(काष्ठा device *dev)
अणु
	dev_pm_करोमुख्य_set(dev, शून्य);
पूर्ण
EXPORT_SYMBOL(vga_चयनeroo_fini_करोमुख्य_pm_ops);
