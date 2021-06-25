<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - चयन/port utility functions
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/idr.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#समावेश "tb.h"

/* Switch NVM support */

#घोषणा NVM_CSS			0x10

काष्ठा nvm_auth_status अणु
	काष्ठा list_head list;
	uuid_t uuid;
	u32 status;
पूर्ण;

क्रमागत nvm_ग_लिखो_ops अणु
	WRITE_AND_AUTHENTICATE = 1,
	WRITE_ONLY = 2,
पूर्ण;

/*
 * Hold NVM authentication failure status per चयन This inक्रमmation
 * needs to stay around even when the चयन माला_लो घातer cycled so we
 * keep it separately.
 */
अटल LIST_HEAD(nvm_auth_status_cache);
अटल DEFINE_MUTEX(nvm_auth_status_lock);

अटल काष्ठा nvm_auth_status *__nvm_get_auth_status(स्थिर काष्ठा tb_चयन *sw)
अणु
	काष्ठा nvm_auth_status *st;

	list_क्रम_each_entry(st, &nvm_auth_status_cache, list) अणु
		अगर (uuid_equal(&st->uuid, sw->uuid))
			वापस st;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम nvm_get_auth_status(स्थिर काष्ठा tb_चयन *sw, u32 *status)
अणु
	काष्ठा nvm_auth_status *st;

	mutex_lock(&nvm_auth_status_lock);
	st = __nvm_get_auth_status(sw);
	mutex_unlock(&nvm_auth_status_lock);

	*status = st ? st->status : 0;
पूर्ण

अटल व्योम nvm_set_auth_status(स्थिर काष्ठा tb_चयन *sw, u32 status)
अणु
	काष्ठा nvm_auth_status *st;

	अगर (WARN_ON(!sw->uuid))
		वापस;

	mutex_lock(&nvm_auth_status_lock);
	st = __nvm_get_auth_status(sw);

	अगर (!st) अणु
		st = kzalloc(माप(*st), GFP_KERNEL);
		अगर (!st)
			जाओ unlock;

		स_नकल(&st->uuid, sw->uuid, माप(st->uuid));
		INIT_LIST_HEAD(&st->list);
		list_add_tail(&st->list, &nvm_auth_status_cache);
	पूर्ण

	st->status = status;
unlock:
	mutex_unlock(&nvm_auth_status_lock);
पूर्ण

अटल व्योम nvm_clear_auth_status(स्थिर काष्ठा tb_चयन *sw)
अणु
	काष्ठा nvm_auth_status *st;

	mutex_lock(&nvm_auth_status_lock);
	st = __nvm_get_auth_status(sw);
	अगर (st) अणु
		list_del(&st->list);
		kमुक्त(st);
	पूर्ण
	mutex_unlock(&nvm_auth_status_lock);
पूर्ण

अटल पूर्णांक nvm_validate_and_ग_लिखो(काष्ठा tb_चयन *sw)
अणु
	अचिन्हित पूर्णांक image_size, hdr_size;
	स्थिर u8 *buf = sw->nvm->buf;
	u16 ds_size;
	पूर्णांक ret;

	अगर (!buf)
		वापस -EINVAL;

	image_size = sw->nvm->buf_data_size;
	अगर (image_size < NVM_MIN_SIZE || image_size > NVM_MAX_SIZE)
		वापस -EINVAL;

	/*
	 * FARB poपूर्णांकer must poपूर्णांक inside the image and must at least
	 * contain parts of the digital section we will be पढ़ोing here.
	 */
	hdr_size = (*(u32 *)buf) & 0xffffff;
	अगर (hdr_size + NVM_DEVID + 2 >= image_size)
		वापस -EINVAL;

	/* Digital section start should be aligned to 4k page */
	अगर (!IS_ALIGNED(hdr_size, SZ_4K))
		वापस -EINVAL;

	/*
	 * Read digital section size and check that it also fits inside
	 * the image.
	 */
	ds_size = *(u16 *)(buf + hdr_size);
	अगर (ds_size >= image_size)
		वापस -EINVAL;

	अगर (!sw->safe_mode) अणु
		u16 device_id;

		/*
		 * Make sure the device ID in the image matches the one
		 * we पढ़ो from the चयन config space.
		 */
		device_id = *(u16 *)(buf + hdr_size + NVM_DEVID);
		अगर (device_id != sw->config.device_id)
			वापस -EINVAL;

		अगर (sw->generation < 3) अणु
			/* Write CSS headers first */
			ret = dma_port_flash_ग_लिखो(sw->dma_port,
				DMA_PORT_CSS_ADDRESS, buf + NVM_CSS,
				DMA_PORT_CSS_MAX_SIZE);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* Skip headers in the image */
		buf += hdr_size;
		image_size -= hdr_size;
	पूर्ण

	अगर (tb_चयन_is_usb4(sw))
		ret = usb4_चयन_nvm_ग_लिखो(sw, 0, buf, image_size);
	अन्यथा
		ret = dma_port_flash_ग_लिखो(sw->dma_port, 0, buf, image_size);
	अगर (!ret)
		sw->nvm->flushed = true;
	वापस ret;
पूर्ण

अटल पूर्णांक nvm_authenticate_host_dma_port(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret = 0;

	/*
	 * Root चयन NVM upgrade requires that we disconnect the
	 * existing paths first (in हाल it is not in safe mode
	 * alपढ़ोy).
	 */
	अगर (!sw->safe_mode) अणु
		u32 status;

		ret = tb_करोमुख्य_disconnect_all_paths(sw->tb);
		अगर (ret)
			वापस ret;
		/*
		 * The host controller goes away pretty soon after this अगर
		 * everything goes well so getting समयout is expected.
		 */
		ret = dma_port_flash_update_auth(sw->dma_port);
		अगर (!ret || ret == -ETIMEDOUT)
			वापस 0;

		/*
		 * Any error from update auth operation requires घातer
		 * cycling of the host router.
		 */
		tb_sw_warn(sw, "failed to authenticate NVM, power cycling\n");
		अगर (dma_port_flash_update_auth_status(sw->dma_port, &status) > 0)
			nvm_set_auth_status(sw, status);
	पूर्ण

	/*
	 * From safe mode we can get out by just घातer cycling the
	 * चयन.
	 */
	dma_port_घातer_cycle(sw->dma_port);
	वापस ret;
पूर्ण

अटल पूर्णांक nvm_authenticate_device_dma_port(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret, retries = 10;

	ret = dma_port_flash_update_auth(sw->dma_port);
	चयन (ret) अणु
	हाल 0:
	हाल -ETIMEDOUT:
	हाल -EACCES:
	हाल -EINVAL:
		/* Power cycle is required */
		अवरोध;
	शेष:
		वापस ret;
	पूर्ण

	/*
	 * Poll here क्रम the authentication status. It takes some समय
	 * क्रम the device to respond (we get समयout क्रम a जबतक). Once
	 * we get response the device needs to be घातer cycled in order
	 * to the new NVM to be taken पूर्णांकo use.
	 */
	करो अणु
		u32 status;

		ret = dma_port_flash_update_auth_status(sw->dma_port, &status);
		अगर (ret < 0 && ret != -ETIMEDOUT)
			वापस ret;
		अगर (ret > 0) अणु
			अगर (status) अणु
				tb_sw_warn(sw, "failed to authenticate NVM\n");
				nvm_set_auth_status(sw, status);
			पूर्ण

			tb_sw_info(sw, "power cycling the switch now\n");
			dma_port_घातer_cycle(sw->dma_port);
			वापस 0;
		पूर्ण

		msleep(500);
	पूर्ण जबतक (--retries);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम nvm_authenticate_start_dma_port(काष्ठा tb_चयन *sw)
अणु
	काष्ठा pci_dev *root_port;

	/*
	 * During host router NVM upgrade we should not allow root port to
	 * go पूर्णांकo D3cold because some root ports cannot trigger PME
	 * itself. To be on the safe side keep the root port in D0 during
	 * the whole upgrade process.
	 */
	root_port = pcie_find_root_port(sw->tb->nhi->pdev);
	अगर (root_port)
		pm_runसमय_get_noresume(&root_port->dev);
पूर्ण

अटल व्योम nvm_authenticate_complete_dma_port(काष्ठा tb_चयन *sw)
अणु
	काष्ठा pci_dev *root_port;

	root_port = pcie_find_root_port(sw->tb->nhi->pdev);
	अगर (root_port)
		pm_runसमय_put(&root_port->dev);
पूर्ण

अटल अंतरभूत bool nvm_पढ़ोable(काष्ठा tb_चयन *sw)
अणु
	अगर (tb_चयन_is_usb4(sw)) अणु
		/*
		 * USB4 devices must support NVM operations but it is
		 * optional क्रम hosts. Thereक्रमe we query the NVM sector
		 * size here and अगर it is supported assume NVM
		 * operations are implemented.
		 */
		वापस usb4_चयन_nvm_sector_size(sw) > 0;
	पूर्ण

	/* Thunderbolt 2 and 3 devices support NVM through DMA port */
	वापस !!sw->dma_port;
पूर्ण

अटल अंतरभूत bool nvm_upgradeable(काष्ठा tb_चयन *sw)
अणु
	अगर (sw->no_nvm_upgrade)
		वापस false;
	वापस nvm_पढ़ोable(sw);
पूर्ण

अटल अंतरभूत पूर्णांक nvm_पढ़ो(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक address,
			   व्योम *buf, माप_प्रकार size)
अणु
	अगर (tb_चयन_is_usb4(sw))
		वापस usb4_चयन_nvm_पढ़ो(sw, address, buf, size);
	वापस dma_port_flash_पढ़ो(sw->dma_port, address, buf, size);
पूर्ण

अटल पूर्णांक nvm_authenticate(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;

	अगर (tb_चयन_is_usb4(sw))
		वापस usb4_चयन_nvm_authenticate(sw);

	अगर (!tb_route(sw)) अणु
		nvm_authenticate_start_dma_port(sw);
		ret = nvm_authenticate_host_dma_port(sw);
	पूर्ण अन्यथा अणु
		ret = nvm_authenticate_device_dma_port(sw);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tb_चयन_nvm_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा tb_nvm *nvm = priv;
	काष्ठा tb_चयन *sw = tb_to_चयन(nvm->dev);
	पूर्णांक ret;

	pm_runसमय_get_sync(&sw->dev);

	अगर (!mutex_trylock(&sw->tb->lock)) अणु
		ret = restart_syscall();
		जाओ out;
	पूर्ण

	ret = nvm_पढ़ो(sw, offset, val, bytes);
	mutex_unlock(&sw->tb->lock);

out:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tb_चयन_nvm_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			       माप_प्रकार bytes)
अणु
	काष्ठा tb_nvm *nvm = priv;
	काष्ठा tb_चयन *sw = tb_to_चयन(nvm->dev);
	पूर्णांक ret;

	अगर (!mutex_trylock(&sw->tb->lock))
		वापस restart_syscall();

	/*
	 * Since writing the NVM image might require some special steps,
	 * क्रम example when CSS headers are written, we cache the image
	 * locally here and handle the special हालs when the user asks
	 * us to authenticate the image.
	 */
	ret = tb_nvm_ग_लिखो_buf(nvm, offset, val, bytes);
	mutex_unlock(&sw->tb->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tb_चयन_nvm_add(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_nvm *nvm;
	u32 val;
	पूर्णांक ret;

	अगर (!nvm_पढ़ोable(sw))
		वापस 0;

	/*
	 * The NVM क्रमmat of non-Intel hardware is not known so
	 * currently restrict NVM upgrade क्रम Intel hardware. We may
	 * relax this in the future when we learn other NVM क्रमmats.
	 */
	अगर (sw->config.venकरोr_id != PCI_VENDOR_ID_INTEL &&
	    sw->config.venकरोr_id != 0x8087) अणु
		dev_info(&sw->dev,
			 "NVM format of vendor %#x is not known, disabling NVM upgrade\n",
			 sw->config.venकरोr_id);
		वापस 0;
	पूर्ण

	nvm = tb_nvm_alloc(&sw->dev);
	अगर (IS_ERR(nvm))
		वापस PTR_ERR(nvm);

	/*
	 * If the चयन is in safe-mode the only accessible portion of
	 * the NVM is the non-active one where userspace is expected to
	 * ग_लिखो new functional NVM.
	 */
	अगर (!sw->safe_mode) अणु
		u32 nvm_size, hdr_size;

		ret = nvm_पढ़ो(sw, NVM_FLASH_SIZE, &val, माप(val));
		अगर (ret)
			जाओ err_nvm;

		hdr_size = sw->generation < 3 ? SZ_8K : SZ_16K;
		nvm_size = (SZ_1M << (val & 7)) / 8;
		nvm_size = (nvm_size - hdr_size) / 2;

		ret = nvm_पढ़ो(sw, NVM_VERSION, &val, माप(val));
		अगर (ret)
			जाओ err_nvm;

		nvm->major = val >> 16;
		nvm->minor = val >> 8;

		ret = tb_nvm_add_active(nvm, nvm_size, tb_चयन_nvm_पढ़ो);
		अगर (ret)
			जाओ err_nvm;
	पूर्ण

	अगर (!sw->no_nvm_upgrade) अणु
		ret = tb_nvm_add_non_active(nvm, NVM_MAX_SIZE,
					    tb_चयन_nvm_ग_लिखो);
		अगर (ret)
			जाओ err_nvm;
	पूर्ण

	sw->nvm = nvm;
	वापस 0;

err_nvm:
	tb_nvm_मुक्त(nvm);
	वापस ret;
पूर्ण

अटल व्योम tb_चयन_nvm_हटाओ(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_nvm *nvm;

	nvm = sw->nvm;
	sw->nvm = शून्य;

	अगर (!nvm)
		वापस;

	/* Remove authentication status in हाल the चयन is unplugged */
	अगर (!nvm->authenticating)
		nvm_clear_auth_status(sw);

	tb_nvm_मुक्त(nvm);
पूर्ण

/* port utility functions */

अटल स्थिर अक्षर *tb_port_type(काष्ठा tb_regs_port_header *port)
अणु
	चयन (port->type >> 16) अणु
	हाल 0:
		चयन ((u8) port->type) अणु
		हाल 0:
			वापस "Inactive";
		हाल 1:
			वापस "Port";
		हाल 2:
			वापस "NHI";
		शेष:
			वापस "unknown";
		पूर्ण
	हाल 0x2:
		वापस "Ethernet";
	हाल 0x8:
		वापस "SATA";
	हाल 0xe:
		वापस "DP/HDMI";
	हाल 0x10:
		वापस "PCIe";
	हाल 0x20:
		वापस "USB";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल व्योम tb_dump_port(काष्ठा tb *tb, काष्ठा tb_regs_port_header *port)
अणु
	tb_dbg(tb,
	       " Port %d: %x:%x (Revision: %d, TB Version: %d, Type: %s (%#x))\n",
	       port->port_number, port->venकरोr_id, port->device_id,
	       port->revision, port->thunderbolt_version, tb_port_type(port),
	       port->type);
	tb_dbg(tb, "  Max hop id (in/out): %d/%d\n",
	       port->max_in_hop_id, port->max_out_hop_id);
	tb_dbg(tb, "  Max counters: %d\n", port->max_counters);
	tb_dbg(tb, "  NFC Credits: %#x\n", port->nfc_credits);
पूर्ण

/**
 * tb_port_state() - get connectedness state of a port
 * @port: the port to check
 *
 * The port must have a TB_CAP_PHY (i.e. it should be a real port).
 *
 * Return: Returns an क्रमागत tb_port_state on success or an error code on failure.
 */
पूर्णांक tb_port_state(काष्ठा tb_port *port)
अणु
	काष्ठा tb_cap_phy phy;
	पूर्णांक res;
	अगर (port->cap_phy == 0) अणु
		tb_port_WARN(port, "does not have a PHY\n");
		वापस -EINVAL;
	पूर्ण
	res = tb_port_पढ़ो(port, &phy, TB_CFG_PORT, port->cap_phy, 2);
	अगर (res)
		वापस res;
	वापस phy.state;
पूर्ण

/**
 * tb_रुको_क्रम_port() - रुको क्रम a port to become पढ़ोy
 * @port: Port to रुको
 * @रुको_अगर_unplugged: Wait also when port is unplugged
 *
 * Wait up to 1 second क्रम a port to reach state TB_PORT_UP. If
 * रुको_अगर_unplugged is set then we also रुको अगर the port is in state
 * TB_PORT_UNPLUGGED (it takes a जबतक क्रम the device to be रेजिस्टरed after
 * चयन resume). Otherwise we only रुको अगर a device is रेजिस्टरed but the link
 * has not yet been established.
 *
 * Return: Returns an error code on failure. Returns 0 अगर the port is not
 * connected or failed to reach state TB_PORT_UP within one second. Returns 1
 * अगर the port is connected and in state TB_PORT_UP.
 */
पूर्णांक tb_रुको_क्रम_port(काष्ठा tb_port *port, bool रुको_अगर_unplugged)
अणु
	पूर्णांक retries = 10;
	पूर्णांक state;
	अगर (!port->cap_phy) अणु
		tb_port_WARN(port, "does not have PHY\n");
		वापस -EINVAL;
	पूर्ण
	अगर (tb_is_upstream_port(port)) अणु
		tb_port_WARN(port, "is the upstream port\n");
		वापस -EINVAL;
	पूर्ण

	जबतक (retries--) अणु
		state = tb_port_state(port);
		अगर (state < 0)
			वापस state;
		अगर (state == TB_PORT_DISABLED) अणु
			tb_port_dbg(port, "is disabled (state: 0)\n");
			वापस 0;
		पूर्ण
		अगर (state == TB_PORT_UNPLUGGED) अणु
			अगर (रुको_अगर_unplugged) अणु
				/* used during resume */
				tb_port_dbg(port,
					    "is unplugged (state: 7), retrying...\n");
				msleep(100);
				जारी;
			पूर्ण
			tb_port_dbg(port, "is unplugged (state: 7)\n");
			वापस 0;
		पूर्ण
		अगर (state == TB_PORT_UP) अणु
			tb_port_dbg(port, "is connected, link is up (state: 2)\n");
			वापस 1;
		पूर्ण

		/*
		 * After plug-in the state is TB_PORT_CONNECTING. Give it some
		 * समय.
		 */
		tb_port_dbg(port,
			    "is connected, link is not up (state: %d), retrying...\n",
			    state);
		msleep(100);
	पूर्ण
	tb_port_warn(port,
		     "failed to reach state TB_PORT_UP. Ignoring port...\n");
	वापस 0;
पूर्ण

/**
 * tb_port_add_nfc_credits() - add/हटाओ non flow controlled credits to port
 * @port: Port to add/हटाओ NFC credits
 * @credits: Credits to add/हटाओ
 *
 * Change the number of NFC credits allocated to @port by @credits. To हटाओ
 * NFC credits pass a negative amount of credits.
 *
 * Return: Returns 0 on success or an error code on failure.
 */
पूर्णांक tb_port_add_nfc_credits(काष्ठा tb_port *port, पूर्णांक credits)
अणु
	u32 nfc_credits;

	अगर (credits == 0 || port->sw->is_unplugged)
		वापस 0;

	/*
	 * USB4 restricts programming NFC buffers to lane adapters only
	 * so skip other ports.
	 */
	अगर (tb_चयन_is_usb4(port->sw) && !tb_port_is_null(port))
		वापस 0;

	nfc_credits = port->config.nfc_credits & ADP_CS_4_NFC_BUFFERS_MASK;
	nfc_credits += credits;

	tb_port_dbg(port, "adding %d NFC credits to %lu", credits,
		    port->config.nfc_credits & ADP_CS_4_NFC_BUFFERS_MASK);

	port->config.nfc_credits &= ~ADP_CS_4_NFC_BUFFERS_MASK;
	port->config.nfc_credits |= nfc_credits;

	वापस tb_port_ग_लिखो(port, &port->config.nfc_credits,
			     TB_CFG_PORT, ADP_CS_4, 1);
पूर्ण

/**
 * tb_port_clear_counter() - clear a counter in TB_CFG_COUNTER
 * @port: Port whose counters to clear
 * @counter: Counter index to clear
 *
 * Return: Returns 0 on success or an error code on failure.
 */
पूर्णांक tb_port_clear_counter(काष्ठा tb_port *port, पूर्णांक counter)
अणु
	u32 zero[3] = अणु 0, 0, 0 पूर्ण;
	tb_port_dbg(port, "clearing counter %d\n", counter);
	वापस tb_port_ग_लिखो(port, zero, TB_CFG_COUNTERS, 3 * counter, 3);
पूर्ण

/**
 * tb_port_unlock() - Unlock करोwnstream port
 * @port: Port to unlock
 *
 * Needed क्रम USB4 but can be called क्रम any CIO/USB4 ports. Makes the
 * करोwnstream router accessible क्रम CM.
 */
पूर्णांक tb_port_unlock(काष्ठा tb_port *port)
अणु
	अगर (tb_चयन_is_icm(port->sw))
		वापस 0;
	अगर (!tb_port_is_null(port))
		वापस -EINVAL;
	अगर (tb_चयन_is_usb4(port->sw))
		वापस usb4_port_unlock(port);
	वापस 0;
पूर्ण

अटल पूर्णांक __tb_port_enable(काष्ठा tb_port *port, bool enable)
अणु
	पूर्णांक ret;
	u32 phy;

	अगर (!tb_port_is_null(port))
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &phy, TB_CFG_PORT,
			   port->cap_phy + LANE_ADP_CS_1, 1);
	अगर (ret)
		वापस ret;

	अगर (enable)
		phy &= ~LANE_ADP_CS_1_LD;
	अन्यथा
		phy |= LANE_ADP_CS_1_LD;

	वापस tb_port_ग_लिखो(port, &phy, TB_CFG_PORT,
			     port->cap_phy + LANE_ADP_CS_1, 1);
पूर्ण

/**
 * tb_port_enable() - Enable lane adapter
 * @port: Port to enable (can be %शून्य)
 *
 * This is used क्रम lane 0 and 1 adapters to enable it.
 */
पूर्णांक tb_port_enable(काष्ठा tb_port *port)
अणु
	वापस __tb_port_enable(port, true);
पूर्ण

/**
 * tb_port_disable() - Disable lane adapter
 * @port: Port to disable (can be %शून्य)
 *
 * This is used क्रम lane 0 and 1 adapters to disable it.
 */
पूर्णांक tb_port_disable(काष्ठा tb_port *port)
अणु
	वापस __tb_port_enable(port, false);
पूर्ण

/*
 * tb_init_port() - initialize a port
 *
 * This is a helper method क्रम tb_चयन_alloc. Does not check or initialize
 * any करोwnstream चयनes.
 *
 * Return: Returns 0 on success or an error code on failure.
 */
अटल पूर्णांक tb_init_port(काष्ठा tb_port *port)
अणु
	पूर्णांक res;
	पूर्णांक cap;

	res = tb_port_पढ़ो(port, &port->config, TB_CFG_PORT, 0, 8);
	अगर (res) अणु
		अगर (res == -ENODEV) अणु
			tb_dbg(port->sw->tb, " Port %d: not implemented\n",
			       port->port);
			port->disabled = true;
			वापस 0;
		पूर्ण
		वापस res;
	पूर्ण

	/* Port 0 is the चयन itself and has no PHY. */
	अगर (port->config.type == TB_TYPE_PORT && port->port != 0) अणु
		cap = tb_port_find_cap(port, TB_PORT_CAP_PHY);

		अगर (cap > 0)
			port->cap_phy = cap;
		अन्यथा
			tb_port_WARN(port, "non switch port without a PHY\n");

		cap = tb_port_find_cap(port, TB_PORT_CAP_USB4);
		अगर (cap > 0)
			port->cap_usb4 = cap;
	पूर्ण अन्यथा अगर (port->port != 0) अणु
		cap = tb_port_find_cap(port, TB_PORT_CAP_ADAP);
		अगर (cap > 0)
			port->cap_adap = cap;
	पूर्ण

	tb_dump_port(port->sw->tb, &port->config);

	INIT_LIST_HEAD(&port->list);
	वापस 0;

पूर्ण

अटल पूर्णांक tb_port_alloc_hopid(काष्ठा tb_port *port, bool in, पूर्णांक min_hopid,
			       पूर्णांक max_hopid)
अणु
	पूर्णांक port_max_hopid;
	काष्ठा ida *ida;

	अगर (in) अणु
		port_max_hopid = port->config.max_in_hop_id;
		ida = &port->in_hopids;
	पूर्ण अन्यथा अणु
		port_max_hopid = port->config.max_out_hop_id;
		ida = &port->out_hopids;
	पूर्ण

	/*
	 * NHI can use HopIDs 1-max क्रम other adapters HopIDs 0-7 are
	 * reserved.
	 */
	अगर (!tb_port_is_nhi(port) && min_hopid < TB_PATH_MIN_HOPID)
		min_hopid = TB_PATH_MIN_HOPID;

	अगर (max_hopid < 0 || max_hopid > port_max_hopid)
		max_hopid = port_max_hopid;

	वापस ida_simple_get(ida, min_hopid, max_hopid + 1, GFP_KERNEL);
पूर्ण

/**
 * tb_port_alloc_in_hopid() - Allocate input HopID from port
 * @port: Port to allocate HopID क्रम
 * @min_hopid: Minimum acceptable input HopID
 * @max_hopid: Maximum acceptable input HopID
 *
 * Return: HopID between @min_hopid and @max_hopid or negative त्रुटि_सं in
 * हाल of error.
 */
पूर्णांक tb_port_alloc_in_hopid(काष्ठा tb_port *port, पूर्णांक min_hopid, पूर्णांक max_hopid)
अणु
	वापस tb_port_alloc_hopid(port, true, min_hopid, max_hopid);
पूर्ण

/**
 * tb_port_alloc_out_hopid() - Allocate output HopID from port
 * @port: Port to allocate HopID क्रम
 * @min_hopid: Minimum acceptable output HopID
 * @max_hopid: Maximum acceptable output HopID
 *
 * Return: HopID between @min_hopid and @max_hopid or negative त्रुटि_सं in
 * हाल of error.
 */
पूर्णांक tb_port_alloc_out_hopid(काष्ठा tb_port *port, पूर्णांक min_hopid, पूर्णांक max_hopid)
अणु
	वापस tb_port_alloc_hopid(port, false, min_hopid, max_hopid);
पूर्ण

/**
 * tb_port_release_in_hopid() - Release allocated input HopID from port
 * @port: Port whose HopID to release
 * @hopid: HopID to release
 */
व्योम tb_port_release_in_hopid(काष्ठा tb_port *port, पूर्णांक hopid)
अणु
	ida_simple_हटाओ(&port->in_hopids, hopid);
पूर्ण

/**
 * tb_port_release_out_hopid() - Release allocated output HopID from port
 * @port: Port whose HopID to release
 * @hopid: HopID to release
 */
व्योम tb_port_release_out_hopid(काष्ठा tb_port *port, पूर्णांक hopid)
अणु
	ida_simple_हटाओ(&port->out_hopids, hopid);
पूर्ण

अटल अंतरभूत bool tb_चयन_is_reachable(स्थिर काष्ठा tb_चयन *parent,
					  स्थिर काष्ठा tb_चयन *sw)
अणु
	u64 mask = (1ULL << parent->config.depth * 8) - 1;
	वापस (tb_route(parent) & mask) == (tb_route(sw) & mask);
पूर्ण

/**
 * tb_next_port_on_path() - Return next port क्रम given port on a path
 * @start: Start port of the walk
 * @end: End port of the walk
 * @prev: Previous port (%शून्य अगर this is the first)
 *
 * This function can be used to walk from one port to another अगर they
 * are connected through zero or more चयनes. If the @prev is dual
 * link port, the function follows that link and वापसs another end on
 * that same link.
 *
 * If the @end port has been reached, वापस %शून्य.
 *
 * Doमुख्य tb->lock must be held when this function is called.
 */
काष्ठा tb_port *tb_next_port_on_path(काष्ठा tb_port *start, काष्ठा tb_port *end,
				     काष्ठा tb_port *prev)
अणु
	काष्ठा tb_port *next;

	अगर (!prev)
		वापस start;

	अगर (prev->sw == end->sw) अणु
		अगर (prev == end)
			वापस शून्य;
		वापस end;
	पूर्ण

	अगर (tb_चयन_is_reachable(prev->sw, end->sw)) अणु
		next = tb_port_at(tb_route(end->sw), prev->sw);
		/* Walk करोwn the topology अगर next == prev */
		अगर (prev->remote &&
		    (next == prev || next->dual_link_port == prev))
			next = prev->remote;
	पूर्ण अन्यथा अणु
		अगर (tb_is_upstream_port(prev)) अणु
			next = prev->remote;
		पूर्ण अन्यथा अणु
			next = tb_upstream_port(prev->sw);
			/*
			 * Keep the same link अगर prev and next are both
			 * dual link ports.
			 */
			अगर (next->dual_link_port &&
			    next->link_nr != prev->link_nr) अणु
				next = next->dual_link_port;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस next != prev ? next : शून्य;
पूर्ण

/**
 * tb_port_get_link_speed() - Get current link speed
 * @port: Port to check (USB4 or CIO)
 *
 * Returns link speed in Gb/s or negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक tb_port_get_link_speed(काष्ठा tb_port *port)
अणु
	u32 val, speed;
	पूर्णांक ret;

	अगर (!port->cap_phy)
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_phy + LANE_ADP_CS_1, 1);
	अगर (ret)
		वापस ret;

	speed = (val & LANE_ADP_CS_1_CURRENT_SPEED_MASK) >>
		LANE_ADP_CS_1_CURRENT_SPEED_SHIFT;
	वापस speed == LANE_ADP_CS_1_CURRENT_SPEED_GEN3 ? 20 : 10;
पूर्ण

/**
 * tb_port_get_link_width() - Get current link width
 * @port: Port to check (USB4 or CIO)
 *
 * Returns link width. Return values can be 1 (Single-Lane), 2 (Dual-Lane)
 * or negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक tb_port_get_link_width(काष्ठा tb_port *port)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (!port->cap_phy)
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_phy + LANE_ADP_CS_1, 1);
	अगर (ret)
		वापस ret;

	वापस (val & LANE_ADP_CS_1_CURRENT_WIDTH_MASK) >>
		LANE_ADP_CS_1_CURRENT_WIDTH_SHIFT;
पूर्ण

अटल bool tb_port_is_width_supported(काष्ठा tb_port *port, पूर्णांक width)
अणु
	u32 phy, widths;
	पूर्णांक ret;

	अगर (!port->cap_phy)
		वापस false;

	ret = tb_port_पढ़ो(port, &phy, TB_CFG_PORT,
			   port->cap_phy + LANE_ADP_CS_0, 1);
	अगर (ret)
		वापस false;

	widths = (phy & LANE_ADP_CS_0_SUPPORTED_WIDTH_MASK) >>
		LANE_ADP_CS_0_SUPPORTED_WIDTH_SHIFT;

	वापस !!(widths & width);
पूर्ण

अटल पूर्णांक tb_port_set_link_width(काष्ठा tb_port *port, अचिन्हित पूर्णांक width)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (!port->cap_phy)
		वापस -EINVAL;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_phy + LANE_ADP_CS_1, 1);
	अगर (ret)
		वापस ret;

	val &= ~LANE_ADP_CS_1_TARGET_WIDTH_MASK;
	चयन (width) अणु
	हाल 1:
		val |= LANE_ADP_CS_1_TARGET_WIDTH_SINGLE <<
			LANE_ADP_CS_1_TARGET_WIDTH_SHIFT;
		अवरोध;
	हाल 2:
		val |= LANE_ADP_CS_1_TARGET_WIDTH_DUAL <<
			LANE_ADP_CS_1_TARGET_WIDTH_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val |= LANE_ADP_CS_1_LB;

	वापस tb_port_ग_लिखो(port, &val, TB_CFG_PORT,
			     port->cap_phy + LANE_ADP_CS_1, 1);
पूर्ण

/**
 * tb_port_lane_bonding_enable() - Enable bonding on port
 * @port: port to enable
 *
 * Enable bonding by setting the link width of the port and the
 * other port in हाल of dual link port.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of error
 */
पूर्णांक tb_port_lane_bonding_enable(काष्ठा tb_port *port)
अणु
	पूर्णांक ret;

	/*
	 * Enable lane bonding क्रम both links अगर not alपढ़ोy enabled by
	 * क्रम example the boot firmware.
	 */
	ret = tb_port_get_link_width(port);
	अगर (ret == 1) अणु
		ret = tb_port_set_link_width(port, 2);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tb_port_get_link_width(port->dual_link_port);
	अगर (ret == 1) अणु
		ret = tb_port_set_link_width(port->dual_link_port, 2);
		अगर (ret) अणु
			tb_port_set_link_width(port, 1);
			वापस ret;
		पूर्ण
	पूर्ण

	port->bonded = true;
	port->dual_link_port->bonded = true;

	वापस 0;
पूर्ण

/**
 * tb_port_lane_bonding_disable() - Disable bonding on port
 * @port: port to disable
 *
 * Disable bonding by setting the link width of the port and the
 * other port in हाल of dual link port.
 *
 */
व्योम tb_port_lane_bonding_disable(काष्ठा tb_port *port)
अणु
	port->dual_link_port->bonded = false;
	port->bonded = false;

	tb_port_set_link_width(port->dual_link_port, 1);
	tb_port_set_link_width(port, 1);
पूर्ण

अटल पूर्णांक tb_port_start_lane_initialization(काष्ठा tb_port *port)
अणु
	पूर्णांक ret;

	अगर (tb_चयन_is_usb4(port->sw))
		वापस 0;

	ret = tb_lc_start_lane_initialization(port);
	वापस ret == -EINVAL ? 0 : ret;
पूर्ण

/**
 * tb_port_is_enabled() - Is the adapter port enabled
 * @port: Port to check
 */
bool tb_port_is_enabled(काष्ठा tb_port *port)
अणु
	चयन (port->config.type) अणु
	हाल TB_TYPE_PCIE_UP:
	हाल TB_TYPE_PCIE_DOWN:
		वापस tb_pci_port_is_enabled(port);

	हाल TB_TYPE_DP_HDMI_IN:
	हाल TB_TYPE_DP_HDMI_OUT:
		वापस tb_dp_port_is_enabled(port);

	हाल TB_TYPE_USB3_UP:
	हाल TB_TYPE_USB3_DOWN:
		वापस tb_usb3_port_is_enabled(port);

	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * tb_usb3_port_is_enabled() - Is the USB3 adapter port enabled
 * @port: USB3 adapter port to check
 */
bool tb_usb3_port_is_enabled(काष्ठा tb_port *port)
अणु
	u32 data;

	अगर (tb_port_पढ़ो(port, &data, TB_CFG_PORT,
			 port->cap_adap + ADP_USB3_CS_0, 1))
		वापस false;

	वापस !!(data & ADP_USB3_CS_0_PE);
पूर्ण

/**
 * tb_usb3_port_enable() - Enable USB3 adapter port
 * @port: USB3 adapter port to enable
 * @enable: Enable/disable the USB3 adapter
 */
पूर्णांक tb_usb3_port_enable(काष्ठा tb_port *port, bool enable)
अणु
	u32 word = enable ? (ADP_USB3_CS_0_PE | ADP_USB3_CS_0_V)
			  : ADP_USB3_CS_0_V;

	अगर (!port->cap_adap)
		वापस -ENXIO;
	वापस tb_port_ग_लिखो(port, &word, TB_CFG_PORT,
			     port->cap_adap + ADP_USB3_CS_0, 1);
पूर्ण

/**
 * tb_pci_port_is_enabled() - Is the PCIe adapter port enabled
 * @port: PCIe port to check
 */
bool tb_pci_port_is_enabled(काष्ठा tb_port *port)
अणु
	u32 data;

	अगर (tb_port_पढ़ो(port, &data, TB_CFG_PORT,
			 port->cap_adap + ADP_PCIE_CS_0, 1))
		वापस false;

	वापस !!(data & ADP_PCIE_CS_0_PE);
पूर्ण

/**
 * tb_pci_port_enable() - Enable PCIe adapter port
 * @port: PCIe port to enable
 * @enable: Enable/disable the PCIe adapter
 */
पूर्णांक tb_pci_port_enable(काष्ठा tb_port *port, bool enable)
अणु
	u32 word = enable ? ADP_PCIE_CS_0_PE : 0x0;
	अगर (!port->cap_adap)
		वापस -ENXIO;
	वापस tb_port_ग_लिखो(port, &word, TB_CFG_PORT,
			     port->cap_adap + ADP_PCIE_CS_0, 1);
पूर्ण

/**
 * tb_dp_port_hpd_is_active() - Is HPD alपढ़ोy active
 * @port: DP out port to check
 *
 * Checks अगर the DP OUT adapter port has HDP bit alपढ़ोy set.
 */
पूर्णांक tb_dp_port_hpd_is_active(काष्ठा tb_port *port)
अणु
	u32 data;
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, &data, TB_CFG_PORT,
			   port->cap_adap + ADP_DP_CS_2, 1);
	अगर (ret)
		वापस ret;

	वापस !!(data & ADP_DP_CS_2_HDP);
पूर्ण

/**
 * tb_dp_port_hpd_clear() - Clear HPD from DP IN port
 * @port: Port to clear HPD
 *
 * If the DP IN port has HDP set, this function can be used to clear it.
 */
पूर्णांक tb_dp_port_hpd_clear(काष्ठा tb_port *port)
अणु
	u32 data;
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, &data, TB_CFG_PORT,
			   port->cap_adap + ADP_DP_CS_3, 1);
	अगर (ret)
		वापस ret;

	data |= ADP_DP_CS_3_HDPC;
	वापस tb_port_ग_लिखो(port, &data, TB_CFG_PORT,
			     port->cap_adap + ADP_DP_CS_3, 1);
पूर्ण

/**
 * tb_dp_port_set_hops() - Set video/aux Hop IDs क्रम DP port
 * @port: DP IN/OUT port to set hops
 * @video: Video Hop ID
 * @aux_tx: AUX TX Hop ID
 * @aux_rx: AUX RX Hop ID
 *
 * Programs specअगरied Hop IDs क्रम DP IN/OUT port.
 */
पूर्णांक tb_dp_port_set_hops(काष्ठा tb_port *port, अचिन्हित पूर्णांक video,
			अचिन्हित पूर्णांक aux_tx, अचिन्हित पूर्णांक aux_rx)
अणु
	u32 data[2];
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, data, TB_CFG_PORT,
			   port->cap_adap + ADP_DP_CS_0, ARRAY_SIZE(data));
	अगर (ret)
		वापस ret;

	data[0] &= ~ADP_DP_CS_0_VIDEO_HOPID_MASK;
	data[1] &= ~ADP_DP_CS_1_AUX_RX_HOPID_MASK;
	data[1] &= ~ADP_DP_CS_1_AUX_RX_HOPID_MASK;

	data[0] |= (video << ADP_DP_CS_0_VIDEO_HOPID_SHIFT) &
		ADP_DP_CS_0_VIDEO_HOPID_MASK;
	data[1] |= aux_tx & ADP_DP_CS_1_AUX_TX_HOPID_MASK;
	data[1] |= (aux_rx << ADP_DP_CS_1_AUX_RX_HOPID_SHIFT) &
		ADP_DP_CS_1_AUX_RX_HOPID_MASK;

	वापस tb_port_ग_लिखो(port, data, TB_CFG_PORT,
			     port->cap_adap + ADP_DP_CS_0, ARRAY_SIZE(data));
पूर्ण

/**
 * tb_dp_port_is_enabled() - Is DP adapter port enabled
 * @port: DP adapter port to check
 */
bool tb_dp_port_is_enabled(काष्ठा tb_port *port)
अणु
	u32 data[2];

	अगर (tb_port_पढ़ो(port, data, TB_CFG_PORT, port->cap_adap + ADP_DP_CS_0,
			 ARRAY_SIZE(data)))
		वापस false;

	वापस !!(data[0] & (ADP_DP_CS_0_VE | ADP_DP_CS_0_AE));
पूर्ण

/**
 * tb_dp_port_enable() - Enables/disables DP paths of a port
 * @port: DP IN/OUT port
 * @enable: Enable/disable DP path
 *
 * Once Hop IDs are programmed DP paths can be enabled or disabled by
 * calling this function.
 */
पूर्णांक tb_dp_port_enable(काष्ठा tb_port *port, bool enable)
अणु
	u32 data[2];
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, data, TB_CFG_PORT,
			  port->cap_adap + ADP_DP_CS_0, ARRAY_SIZE(data));
	अगर (ret)
		वापस ret;

	अगर (enable)
		data[0] |= ADP_DP_CS_0_VE | ADP_DP_CS_0_AE;
	अन्यथा
		data[0] &= ~(ADP_DP_CS_0_VE | ADP_DP_CS_0_AE);

	वापस tb_port_ग_लिखो(port, data, TB_CFG_PORT,
			     port->cap_adap + ADP_DP_CS_0, ARRAY_SIZE(data));
पूर्ण

/* चयन utility functions */

अटल स्थिर अक्षर *tb_चयन_generation_name(स्थिर काष्ठा tb_चयन *sw)
अणु
	चयन (sw->generation) अणु
	हाल 1:
		वापस "Thunderbolt 1";
	हाल 2:
		वापस "Thunderbolt 2";
	हाल 3:
		वापस "Thunderbolt 3";
	हाल 4:
		वापस "USB4";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल व्योम tb_dump_चयन(स्थिर काष्ठा tb *tb, स्थिर काष्ठा tb_चयन *sw)
अणु
	स्थिर काष्ठा tb_regs_चयन_header *regs = &sw->config;

	tb_dbg(tb, " %s Switch: %x:%x (Revision: %d, TB Version: %d)\n",
	       tb_चयन_generation_name(sw), regs->venकरोr_id, regs->device_id,
	       regs->revision, regs->thunderbolt_version);
	tb_dbg(tb, "  Max Port Number: %d\n", regs->max_port_number);
	tb_dbg(tb, "  Config:\n");
	tb_dbg(tb,
		"   Upstream Port Number: %d Depth: %d Route String: %#llx Enabled: %d, PlugEventsDelay: %dms\n",
	       regs->upstream_port_number, regs->depth,
	       (((u64) regs->route_hi) << 32) | regs->route_lo,
	       regs->enabled, regs->plug_events_delay);
	tb_dbg(tb, "   unknown1: %#x unknown4: %#x\n",
	       regs->__unknown1, regs->__unknown4);
पूर्ण

/**
 * tb_चयन_reset() - reconfigure route, enable and send TB_CFG_PKG_RESET
 * @sw: Switch to reset
 *
 * Return: Returns 0 on success or an error code on failure.
 */
पूर्णांक tb_चयन_reset(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_cfg_result res;

	अगर (sw->generation > 1)
		वापस 0;

	tb_sw_dbg(sw, "resetting switch\n");

	res.err = tb_sw_ग_लिखो(sw, ((u32 *) &sw->config) + 2,
			      TB_CFG_SWITCH, 2, 2);
	अगर (res.err)
		वापस res.err;
	res = tb_cfg_reset(sw->tb->ctl, tb_route(sw));
	अगर (res.err > 0)
		वापस -EIO;
	वापस res.err;
पूर्ण

/*
 * tb_plug_events_active() - enable/disable plug events on a चयन
 *
 * Also configures a sane plug_events_delay of 255ms.
 *
 * Return: Returns 0 on success or an error code on failure.
 */
अटल पूर्णांक tb_plug_events_active(काष्ठा tb_चयन *sw, bool active)
अणु
	u32 data;
	पूर्णांक res;

	अगर (tb_चयन_is_icm(sw) || tb_चयन_is_usb4(sw))
		वापस 0;

	sw->config.plug_events_delay = 0xff;
	res = tb_sw_ग_लिखो(sw, ((u32 *) &sw->config) + 4, TB_CFG_SWITCH, 4, 1);
	अगर (res)
		वापस res;

	res = tb_sw_पढ़ो(sw, &data, TB_CFG_SWITCH, sw->cap_plug_events + 1, 1);
	अगर (res)
		वापस res;

	अगर (active) अणु
		data = data & 0xFFFFFF83;
		चयन (sw->config.device_id) अणु
		हाल PCI_DEVICE_ID_INTEL_LIGHT_RIDGE:
		हाल PCI_DEVICE_ID_INTEL_EAGLE_RIDGE:
		हाल PCI_DEVICE_ID_INTEL_PORT_RIDGE:
			अवरोध;
		शेष:
			data |= 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		data = data | 0x7c;
	पूर्ण
	वापस tb_sw_ग_लिखो(sw, &data, TB_CFG_SWITCH,
			   sw->cap_plug_events + 1, 1);
पूर्ण

अटल sमाप_प्रकार authorized_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%u\n", sw->authorized);
पूर्ण

अटल पूर्णांक disapprove_चयन(काष्ठा device *dev, व्योम *not_used)
अणु
	काष्ठा tb_चयन *sw;

	sw = tb_to_चयन(dev);
	अगर (sw && sw->authorized) अणु
		पूर्णांक ret;

		/* First children */
		ret = device_क्रम_each_child_reverse(&sw->dev, शून्य, disapprove_चयन);
		अगर (ret)
			वापस ret;

		ret = tb_करोमुख्य_disapprove_चयन(sw->tb, sw);
		अगर (ret)
			वापस ret;

		sw->authorized = 0;
		kobject_uevent(&sw->dev.kobj, KOBJ_CHANGE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tb_चयन_set_authorized(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!mutex_trylock(&sw->tb->lock))
		वापस restart_syscall();

	अगर (!!sw->authorized == !!val)
		जाओ unlock;

	चयन (val) अणु
	/* Disapprove चयन */
	हाल 0:
		अगर (tb_route(sw)) अणु
			ret = disapprove_चयन(&sw->dev, शून्य);
			जाओ unlock;
		पूर्ण
		अवरोध;

	/* Approve चयन */
	हाल 1:
		अगर (sw->key)
			ret = tb_करोमुख्य_approve_चयन_key(sw->tb, sw);
		अन्यथा
			ret = tb_करोमुख्य_approve_चयन(sw->tb, sw);
		अवरोध;

	/* Challenge चयन */
	हाल 2:
		अगर (sw->key)
			ret = tb_करोमुख्य_challenge_चयन_key(sw->tb, sw);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		sw->authorized = val;
		/* Notअगरy status change to the userspace */
		kobject_uevent(&sw->dev.kobj, KOBJ_CHANGE);
	पूर्ण

unlock:
	mutex_unlock(&sw->tb->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार authorized_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	अचिन्हित पूर्णांक val;
	sमाप_प्रकार ret;

	ret = kstrtouपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;
	अगर (val > 2)
		वापस -EINVAL;

	pm_runसमय_get_sync(&sw->dev);
	ret = tb_चयन_set_authorized(sw, val);
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(authorized);

अटल sमाप_प्रकार boot_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%u\n", sw->boot);
पूर्ण
अटल DEVICE_ATTR_RO(boot);

अटल sमाप_प्रकार device_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%#x\n", sw->device);
पूर्ण
अटल DEVICE_ATTR_RO(device);

अटल sमाप_प्रकार
device_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%s\n", sw->device_name ? sw->device_name : "");
पूर्ण
अटल DEVICE_ATTR_RO(device_name);

अटल sमाप_प्रकार
generation_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%u\n", sw->generation);
पूर्ण
अटल DEVICE_ATTR_RO(generation);

अटल sमाप_प्रकार key_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	sमाप_प्रकार ret;

	अगर (!mutex_trylock(&sw->tb->lock))
		वापस restart_syscall();

	अगर (sw->key)
		ret = प्र_लिखो(buf, "%*phN\n", TB_SWITCH_KEY_SIZE, sw->key);
	अन्यथा
		ret = प्र_लिखो(buf, "\n");

	mutex_unlock(&sw->tb->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार key_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	u8 key[TB_SWITCH_KEY_SIZE];
	sमाप_प्रकार ret = count;
	bool clear = false;

	अगर (!म_भेद(buf, "\n"))
		clear = true;
	अन्यथा अगर (hex2bin(key, buf, माप(key)))
		वापस -EINVAL;

	अगर (!mutex_trylock(&sw->tb->lock))
		वापस restart_syscall();

	अगर (sw->authorized) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		kमुक्त(sw->key);
		अगर (clear) अणु
			sw->key = शून्य;
		पूर्ण अन्यथा अणु
			sw->key = kmemdup(key, माप(key), GFP_KERNEL);
			अगर (!sw->key)
				ret = -ENOMEM;
		पूर्ण
	पूर्ण

	mutex_unlock(&sw->tb->lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR(key, 0600, key_show, key_store);

अटल sमाप_प्रकार speed_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%u.0 Gb/s\n", sw->link_speed);
पूर्ण

/*
 * Currently all lanes must run at the same speed but we expose here
 * both directions to allow possible asymmetric links in the future.
 */
अटल DEVICE_ATTR(rx_speed, 0444, speed_show, शून्य);
अटल DEVICE_ATTR(tx_speed, 0444, speed_show, शून्य);

अटल sमाप_प्रकार lanes_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%u\n", sw->link_width);
पूर्ण

/*
 * Currently link has same amount of lanes both directions (1 or 2) but
 * expose them separately to allow possible asymmetric links in the future.
 */
अटल DEVICE_ATTR(rx_lanes, 0444, lanes_show, शून्य);
अटल DEVICE_ATTR(tx_lanes, 0444, lanes_show, शून्य);

अटल sमाप_प्रकार nvm_authenticate_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	u32 status;

	nvm_get_auth_status(sw, &status);
	वापस प्र_लिखो(buf, "%#x\n", status);
पूर्ण

अटल sमाप_प्रकार nvm_authenticate_sysfs(काष्ठा device *dev, स्थिर अक्षर *buf,
				      bool disconnect)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	पूर्णांक val;
	पूर्णांक ret;

	pm_runसमय_get_sync(&sw->dev);

	अगर (!mutex_trylock(&sw->tb->lock)) अणु
		ret = restart_syscall();
		जाओ निकास_rpm;
	पूर्ण

	/* If NVMem devices are not yet added */
	अगर (!sw->nvm) अणु
		ret = -EAGAIN;
		जाओ निकास_unlock;
	पूर्ण

	ret = kstrtoपूर्णांक(buf, 10, &val);
	अगर (ret)
		जाओ निकास_unlock;

	/* Always clear the authentication status */
	nvm_clear_auth_status(sw);

	अगर (val > 0) अणु
		अगर (!sw->nvm->flushed) अणु
			अगर (!sw->nvm->buf) अणु
				ret = -EINVAL;
				जाओ निकास_unlock;
			पूर्ण

			ret = nvm_validate_and_ग_लिखो(sw);
			अगर (ret || val == WRITE_ONLY)
				जाओ निकास_unlock;
		पूर्ण
		अगर (val == WRITE_AND_AUTHENTICATE) अणु
			अगर (disconnect) अणु
				ret = tb_lc_क्रमce_घातer(sw);
			पूर्ण अन्यथा अणु
				sw->nvm->authenticating = true;
				ret = nvm_authenticate(sw);
			पूर्ण
		पूर्ण
	पूर्ण

निकास_unlock:
	mutex_unlock(&sw->tb->lock);
निकास_rpm:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार nvm_authenticate_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = nvm_authenticate_sysfs(dev, buf, false);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(nvm_authenticate);

अटल sमाप_प्रकार nvm_authenticate_on_disconnect_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस nvm_authenticate_show(dev, attr, buf);
पूर्ण

अटल sमाप_प्रकार nvm_authenticate_on_disconnect_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = nvm_authenticate_sysfs(dev, buf, true);
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(nvm_authenticate_on_disconnect);

अटल sमाप_प्रकार nvm_version_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	पूर्णांक ret;

	अगर (!mutex_trylock(&sw->tb->lock))
		वापस restart_syscall();

	अगर (sw->safe_mode)
		ret = -ENODATA;
	अन्यथा अगर (!sw->nvm)
		ret = -EAGAIN;
	अन्यथा
		ret = प्र_लिखो(buf, "%x.%x\n", sw->nvm->major, sw->nvm->minor);

	mutex_unlock(&sw->tb->lock);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(nvm_version);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%#x\n", sw->venकरोr);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल sमाप_प्रकार
venकरोr_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%s\n", sw->venकरोr_name ? sw->venकरोr_name : "");
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr_name);

अटल sमाप_प्रकार unique_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	वापस प्र_लिखो(buf, "%pUb\n", sw->uuid);
पूर्ण
अटल DEVICE_ATTR_RO(unique_id);

अटल काष्ठा attribute *चयन_attrs[] = अणु
	&dev_attr_authorized.attr,
	&dev_attr_boot.attr,
	&dev_attr_device.attr,
	&dev_attr_device_name.attr,
	&dev_attr_generation.attr,
	&dev_attr_key.attr,
	&dev_attr_nvm_authenticate.attr,
	&dev_attr_nvm_authenticate_on_disconnect.attr,
	&dev_attr_nvm_version.attr,
	&dev_attr_rx_speed.attr,
	&dev_attr_rx_lanes.attr,
	&dev_attr_tx_speed.attr,
	&dev_attr_tx_lanes.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_venकरोr_name.attr,
	&dev_attr_unique_id.attr,
	शून्य,
पूर्ण;

अटल bool has_port(स्थिर काष्ठा tb_चयन *sw, क्रमागत tb_port_type type)
अणु
	स्थिर काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!port->disabled && port->config.type == type)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल umode_t चयन_attr_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	अगर (attr == &dev_attr_authorized.attr) अणु
		अगर (sw->tb->security_level == TB_SECURITY_NOPCIE ||
		    sw->tb->security_level == TB_SECURITY_DPONLY ||
		    !has_port(sw, TB_TYPE_PCIE_UP))
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_device.attr) अणु
		अगर (!sw->device)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_device_name.attr) अणु
		अगर (!sw->device_name)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_venकरोr.attr)  अणु
		अगर (!sw->venकरोr)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_venकरोr_name.attr)  अणु
		अगर (!sw->venकरोr_name)
			वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_key.attr) अणु
		अगर (tb_route(sw) &&
		    sw->tb->security_level == TB_SECURITY_SECURE &&
		    sw->security_level == TB_SECURITY_SECURE)
			वापस attr->mode;
		वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_rx_speed.attr ||
		   attr == &dev_attr_rx_lanes.attr ||
		   attr == &dev_attr_tx_speed.attr ||
		   attr == &dev_attr_tx_lanes.attr) अणु
		अगर (tb_route(sw))
			वापस attr->mode;
		वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_nvm_authenticate.attr) अणु
		अगर (nvm_upgradeable(sw))
			वापस attr->mode;
		वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_nvm_version.attr) अणु
		अगर (nvm_पढ़ोable(sw))
			वापस attr->mode;
		वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_boot.attr) अणु
		अगर (tb_route(sw))
			वापस attr->mode;
		वापस 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_nvm_authenticate_on_disconnect.attr) अणु
		अगर (sw->quirks & QUIRK_FORCE_POWER_LINK_CONTROLLER)
			वापस attr->mode;
		वापस 0;
	पूर्ण

	वापस sw->safe_mode ? 0 : attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group चयन_group = अणु
	.is_visible = चयन_attr_is_visible,
	.attrs = चयन_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *चयन_groups[] = अणु
	&चयन_group,
	शून्य,
पूर्ण;

अटल व्योम tb_चयन_release(काष्ठा device *dev)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	काष्ठा tb_port *port;

	dma_port_मुक्त(sw->dma_port);

	tb_चयन_क्रम_each_port(sw, port) अणु
		ida_destroy(&port->in_hopids);
		ida_destroy(&port->out_hopids);
	पूर्ण

	kमुक्त(sw->uuid);
	kमुक्त(sw->device_name);
	kमुक्त(sw->venकरोr_name);
	kमुक्त(sw->ports);
	kमुक्त(sw->drom);
	kमुक्त(sw->key);
	kमुक्त(sw);
पूर्ण

अटल पूर्णांक tb_चयन_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	स्थिर अक्षर *type;

	अगर (sw->config.thunderbolt_version == USB4_VERSION_1_0) अणु
		अगर (add_uevent_var(env, "USB4_VERSION=1.0"))
			वापस -ENOMEM;
	पूर्ण

	अगर (!tb_route(sw)) अणु
		type = "host";
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा tb_port *port;
		bool hub = false;

		/* Device is hub अगर it has any करोwnstream ports */
		tb_चयन_क्रम_each_port(sw, port) अणु
			अगर (!port->disabled && !tb_is_upstream_port(port) &&
			     tb_port_is_null(port)) अणु
				hub = true;
				अवरोध;
			पूर्ण
		पूर्ण

		type = hub ? "hub" : "device";
	पूर्ण

	अगर (add_uevent_var(env, "USB4_TYPE=%s", type))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/*
 * Currently only need to provide the callbacks. Everything अन्यथा is handled
 * in the connection manager.
 */
अटल पूर्णांक __maybe_unused tb_चयन_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	स्थिर काष्ठा tb_cm_ops *cm_ops = sw->tb->cm_ops;

	अगर (cm_ops->runसमय_suspend_चयन)
		वापस cm_ops->runसमय_suspend_चयन(sw);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tb_चयन_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	स्थिर काष्ठा tb_cm_ops *cm_ops = sw->tb->cm_ops;

	अगर (cm_ops->runसमय_resume_चयन)
		वापस cm_ops->runसमय_resume_चयन(sw);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tb_चयन_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tb_चयन_runसमय_suspend, tb_चयन_runसमय_resume,
			   शून्य)
पूर्ण;

काष्ठा device_type tb_चयन_type = अणु
	.name = "thunderbolt_device",
	.release = tb_चयन_release,
	.uevent = tb_चयन_uevent,
	.pm = &tb_चयन_pm_ops,
पूर्ण;

अटल पूर्णांक tb_चयन_get_generation(काष्ठा tb_चयन *sw)
अणु
	चयन (sw->config.device_id) अणु
	हाल PCI_DEVICE_ID_INTEL_LIGHT_RIDGE:
	हाल PCI_DEVICE_ID_INTEL_EAGLE_RIDGE:
	हाल PCI_DEVICE_ID_INTEL_LIGHT_PEAK:
	हाल PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_2C:
	हाल PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C:
	हाल PCI_DEVICE_ID_INTEL_PORT_RIDGE:
	हाल PCI_DEVICE_ID_INTEL_REDWOOD_RIDGE_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_REDWOOD_RIDGE_4C_BRIDGE:
		वापस 1;

	हाल PCI_DEVICE_ID_INTEL_WIN_RIDGE_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_4C_BRIDGE:
		वापस 2;

	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ICL_NHI0:
	हाल PCI_DEVICE_ID_INTEL_ICL_NHI1:
		वापस 3;

	शेष:
		अगर (tb_चयन_is_usb4(sw))
			वापस 4;

		/*
		 * For unknown चयनes assume generation to be 1 to be
		 * on the safe side.
		 */
		tb_sw_warn(sw, "unsupported switch device id %#x\n",
			   sw->config.device_id);
		वापस 1;
	पूर्ण
पूर्ण

अटल bool tb_चयन_exceeds_max_depth(स्थिर काष्ठा tb_चयन *sw, पूर्णांक depth)
अणु
	पूर्णांक max_depth;

	अगर (tb_चयन_is_usb4(sw) ||
	    (sw->tb->root_चयन && tb_चयन_is_usb4(sw->tb->root_चयन)))
		max_depth = USB4_SWITCH_MAX_DEPTH;
	अन्यथा
		max_depth = TB_SWITCH_MAX_DEPTH;

	वापस depth > max_depth;
पूर्ण

/**
 * tb_चयन_alloc() - allocate a चयन
 * @tb: Poपूर्णांकer to the owning करोमुख्य
 * @parent: Parent device क्रम this चयन
 * @route: Route string क्रम this चयन
 *
 * Allocates and initializes a चयन. Will not upload configuration to
 * the चयन. For that you need to call tb_चयन_configure()
 * separately. The वापसed चयन should be released by calling
 * tb_चयन_put().
 *
 * Return: Poपूर्णांकer to the allocated चयन or ERR_PTR() in हाल of
 * failure.
 */
काष्ठा tb_चयन *tb_चयन_alloc(काष्ठा tb *tb, काष्ठा device *parent,
				  u64 route)
अणु
	काष्ठा tb_चयन *sw;
	पूर्णांक upstream_port;
	पूर्णांक i, ret, depth;

	/* Unlock the करोwnstream port so we can access the चयन below */
	अगर (route) अणु
		काष्ठा tb_चयन *parent_sw = tb_to_चयन(parent);
		काष्ठा tb_port *करोwn;

		करोwn = tb_port_at(route, parent_sw);
		tb_port_unlock(करोwn);
	पूर्ण

	depth = tb_route_length(route);

	upstream_port = tb_cfg_get_upstream_port(tb->ctl, route);
	अगर (upstream_port < 0)
		वापस ERR_PTR(upstream_port);

	sw = kzalloc(माप(*sw), GFP_KERNEL);
	अगर (!sw)
		वापस ERR_PTR(-ENOMEM);

	sw->tb = tb;
	ret = tb_cfg_पढ़ो(tb->ctl, &sw->config, route, 0, TB_CFG_SWITCH, 0, 5);
	अगर (ret)
		जाओ err_मुक्त_sw_ports;

	sw->generation = tb_चयन_get_generation(sw);

	tb_dbg(tb, "current switch config:\n");
	tb_dump_चयन(tb, sw);

	/* configure चयन */
	sw->config.upstream_port_number = upstream_port;
	sw->config.depth = depth;
	sw->config.route_hi = upper_32_bits(route);
	sw->config.route_lo = lower_32_bits(route);
	sw->config.enabled = 0;

	/* Make sure we करो not exceed maximum topology limit */
	अगर (tb_चयन_exceeds_max_depth(sw, depth)) अणु
		ret = -EADDRNOTAVAIL;
		जाओ err_मुक्त_sw_ports;
	पूर्ण

	/* initialize ports */
	sw->ports = kसुस्मृति(sw->config.max_port_number + 1, माप(*sw->ports),
				GFP_KERNEL);
	अगर (!sw->ports) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_sw_ports;
	पूर्ण

	क्रम (i = 0; i <= sw->config.max_port_number; i++) अणु
		/* minimum setup क्रम tb_find_cap and tb_drom_पढ़ो to work */
		sw->ports[i].sw = sw;
		sw->ports[i].port = i;

		/* Control port करोes not need HopID allocation */
		अगर (i) अणु
			ida_init(&sw->ports[i].in_hopids);
			ida_init(&sw->ports[i].out_hopids);
		पूर्ण
	पूर्ण

	ret = tb_चयन_find_vse_cap(sw, TB_VSE_CAP_PLUG_EVENTS);
	अगर (ret > 0)
		sw->cap_plug_events = ret;

	ret = tb_चयन_find_vse_cap(sw, TB_VSE_CAP_LINK_CONTROLLER);
	अगर (ret > 0)
		sw->cap_lc = ret;

	/* Root चयन is always authorized */
	अगर (!route)
		sw->authorized = true;

	device_initialize(&sw->dev);
	sw->dev.parent = parent;
	sw->dev.bus = &tb_bus_type;
	sw->dev.type = &tb_चयन_type;
	sw->dev.groups = चयन_groups;
	dev_set_name(&sw->dev, "%u-%llx", tb->index, tb_route(sw));

	वापस sw;

err_मुक्त_sw_ports:
	kमुक्त(sw->ports);
	kमुक्त(sw);

	वापस ERR_PTR(ret);
पूर्ण

/**
 * tb_चयन_alloc_safe_mode() - allocate a चयन that is in safe mode
 * @tb: Poपूर्णांकer to the owning करोमुख्य
 * @parent: Parent device क्रम this चयन
 * @route: Route string क्रम this चयन
 *
 * This creates a चयन in safe mode. This means the चयन pretty much
 * lacks all capabilities except DMA configuration port beक्रमe it is
 * flashed with a valid NVM firmware.
 *
 * The वापसed चयन must be released by calling tb_चयन_put().
 *
 * Return: Poपूर्णांकer to the allocated चयन or ERR_PTR() in हाल of failure
 */
काष्ठा tb_चयन *
tb_चयन_alloc_safe_mode(काष्ठा tb *tb, काष्ठा device *parent, u64 route)
अणु
	काष्ठा tb_चयन *sw;

	sw = kzalloc(माप(*sw), GFP_KERNEL);
	अगर (!sw)
		वापस ERR_PTR(-ENOMEM);

	sw->tb = tb;
	sw->config.depth = tb_route_length(route);
	sw->config.route_hi = upper_32_bits(route);
	sw->config.route_lo = lower_32_bits(route);
	sw->safe_mode = true;

	device_initialize(&sw->dev);
	sw->dev.parent = parent;
	sw->dev.bus = &tb_bus_type;
	sw->dev.type = &tb_चयन_type;
	sw->dev.groups = चयन_groups;
	dev_set_name(&sw->dev, "%u-%llx", tb->index, tb_route(sw));

	वापस sw;
पूर्ण

/**
 * tb_चयन_configure() - Uploads configuration to the चयन
 * @sw: Switch to configure
 *
 * Call this function beक्रमe the चयन is added to the प्रणाली. It will
 * upload configuration to the चयन and makes it available क्रम the
 * connection manager to use. Can be called to the चयन again after
 * resume from low घातer states to re-initialize it.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of failure
 */
पूर्णांक tb_चयन_configure(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb *tb = sw->tb;
	u64 route;
	पूर्णांक ret;

	route = tb_route(sw);

	tb_dbg(tb, "%s Switch at %#llx (depth: %d, up port: %d)\n",
	       sw->config.enabled ? "restoring" : "initializing", route,
	       tb_route_length(route), sw->config.upstream_port_number);

	sw->config.enabled = 1;

	अगर (tb_चयन_is_usb4(sw)) अणु
		/*
		 * For USB4 devices, we need to program the CM version
		 * accordingly so that it knows to expose all the
		 * additional capabilities.
		 */
		sw->config.cmuv = USB4_VERSION_1_0;

		/* Enumerate the चयन */
		ret = tb_sw_ग_लिखो(sw, (u32 *)&sw->config + 1, TB_CFG_SWITCH,
				  ROUTER_CS_1, 4);
		अगर (ret)
			वापस ret;

		ret = usb4_चयन_setup(sw);
	पूर्ण अन्यथा अणु
		अगर (sw->config.venकरोr_id != PCI_VENDOR_ID_INTEL)
			tb_sw_warn(sw, "unknown switch vendor id %#x\n",
				   sw->config.venकरोr_id);

		अगर (!sw->cap_plug_events) अणु
			tb_sw_warn(sw, "cannot find TB_VSE_CAP_PLUG_EVENTS aborting\n");
			वापस -ENODEV;
		पूर्ण

		/* Enumerate the चयन */
		ret = tb_sw_ग_लिखो(sw, (u32 *)&sw->config + 1, TB_CFG_SWITCH,
				  ROUTER_CS_1, 3);
	पूर्ण
	अगर (ret)
		वापस ret;

	वापस tb_plug_events_active(sw, true);
पूर्ण

अटल पूर्णांक tb_चयन_set_uuid(काष्ठा tb_चयन *sw)
अणु
	bool uid = false;
	u32 uuid[4];
	पूर्णांक ret;

	अगर (sw->uuid)
		वापस 0;

	अगर (tb_चयन_is_usb4(sw)) अणु
		ret = usb4_चयन_पढ़ो_uid(sw, &sw->uid);
		अगर (ret)
			वापस ret;
		uid = true;
	पूर्ण अन्यथा अणु
		/*
		 * The newer controllers include fused UUID as part of
		 * link controller specअगरic रेजिस्टरs
		 */
		ret = tb_lc_पढ़ो_uuid(sw, uuid);
		अगर (ret) अणु
			अगर (ret != -EINVAL)
				वापस ret;
			uid = true;
		पूर्ण
	पूर्ण

	अगर (uid) अणु
		/*
		 * ICM generates UUID based on UID and fills the upper
		 * two words with ones. This is not strictly following
		 * UUID क्रमmat but we want to be compatible with it so
		 * we करो the same here.
		 */
		uuid[0] = sw->uid & 0xffffffff;
		uuid[1] = (sw->uid >> 32) & 0xffffffff;
		uuid[2] = 0xffffffff;
		uuid[3] = 0xffffffff;
	पूर्ण

	sw->uuid = kmemdup(uuid, माप(uuid), GFP_KERNEL);
	अगर (!sw->uuid)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक tb_चयन_add_dma_port(काष्ठा tb_चयन *sw)
अणु
	u32 status;
	पूर्णांक ret;

	चयन (sw->generation) अणु
	हाल 2:
		/* Only root चयन can be upgraded */
		अगर (tb_route(sw))
			वापस 0;

		fallthrough;
	हाल 3:
	हाल 4:
		ret = tb_चयन_set_uuid(sw);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		/*
		 * DMA port is the only thing available when the चयन
		 * is in safe mode.
		 */
		अगर (!sw->safe_mode)
			वापस 0;
		अवरोध;
	पूर्ण

	अगर (sw->no_nvm_upgrade)
		वापस 0;

	अगर (tb_चयन_is_usb4(sw)) अणु
		ret = usb4_चयन_nvm_authenticate_status(sw, &status);
		अगर (ret)
			वापस ret;

		अगर (status) अणु
			tb_sw_info(sw, "switch flash authentication failed\n");
			nvm_set_auth_status(sw, status);
		पूर्ण

		वापस 0;
	पूर्ण

	/* Root चयन DMA port requires running firmware */
	अगर (!tb_route(sw) && !tb_चयन_is_icm(sw))
		वापस 0;

	sw->dma_port = dma_port_alloc(sw);
	अगर (!sw->dma_port)
		वापस 0;

	/*
	 * If there is status alपढ़ोy set then authentication failed
	 * when the dma_port_flash_update_auth() वापसed. Power cycling
	 * is not needed (it was करोne alपढ़ोy) so only thing we करो here
	 * is to unblock runसमय PM of the root port.
	 */
	nvm_get_auth_status(sw, &status);
	अगर (status) अणु
		अगर (!tb_route(sw))
			nvm_authenticate_complete_dma_port(sw);
		वापस 0;
	पूर्ण

	/*
	 * Check status of the previous flash authentication. If there
	 * is one we need to घातer cycle the चयन in any हाल to make
	 * it functional again.
	 */
	ret = dma_port_flash_update_auth_status(sw->dma_port, &status);
	अगर (ret <= 0)
		वापस ret;

	/* Now we can allow root port to suspend again */
	अगर (!tb_route(sw))
		nvm_authenticate_complete_dma_port(sw);

	अगर (status) अणु
		tb_sw_info(sw, "switch flash authentication failed\n");
		nvm_set_auth_status(sw, status);
	पूर्ण

	tb_sw_info(sw, "power cycling the switch now\n");
	dma_port_घातer_cycle(sw->dma_port);

	/*
	 * We वापस error here which causes the चयन adding failure.
	 * It should appear back after घातer cycle is complete.
	 */
	वापस -ESHUTDOWN;
पूर्ण

अटल व्योम tb_चयन_शेष_link_ports(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= sw->config.max_port_number; i += 2) अणु
		काष्ठा tb_port *port = &sw->ports[i];
		काष्ठा tb_port *subordinate;

		अगर (!tb_port_is_null(port))
			जारी;

		/* Check क्रम the subordinate port */
		अगर (i == sw->config.max_port_number ||
		    !tb_port_is_null(&sw->ports[i + 1]))
			जारी;

		/* Link them अगर not alपढ़ोy करोne so (by DROM) */
		subordinate = &sw->ports[i + 1];
		अगर (!port->dual_link_port && !subordinate->dual_link_port) अणु
			port->link_nr = 0;
			port->dual_link_port = subordinate;
			subordinate->link_nr = 1;
			subordinate->dual_link_port = port;

			tb_sw_dbg(sw, "linked ports %d <-> %d\n",
				  port->port, subordinate->port);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool tb_चयन_lane_bonding_possible(काष्ठा tb_चयन *sw)
अणु
	स्थिर काष्ठा tb_port *up = tb_upstream_port(sw);

	अगर (!up->dual_link_port || !up->dual_link_port->remote)
		वापस false;

	अगर (tb_चयन_is_usb4(sw))
		वापस usb4_चयन_lane_bonding_possible(sw);
	वापस tb_lc_lane_bonding_possible(sw);
पूर्ण

अटल पूर्णांक tb_चयन_update_link_attributes(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *up;
	bool change = false;
	पूर्णांक ret;

	अगर (!tb_route(sw) || tb_चयन_is_icm(sw))
		वापस 0;

	up = tb_upstream_port(sw);

	ret = tb_port_get_link_speed(up);
	अगर (ret < 0)
		वापस ret;
	अगर (sw->link_speed != ret)
		change = true;
	sw->link_speed = ret;

	ret = tb_port_get_link_width(up);
	अगर (ret < 0)
		वापस ret;
	अगर (sw->link_width != ret)
		change = true;
	sw->link_width = ret;

	/* Notअगरy userspace that there is possible link attribute change */
	अगर (device_is_रेजिस्टरed(&sw->dev) && change)
		kobject_uevent(&sw->dev.kobj, KOBJ_CHANGE);

	वापस 0;
पूर्ण

/**
 * tb_चयन_lane_bonding_enable() - Enable lane bonding
 * @sw: Switch to enable lane bonding
 *
 * Connection manager can call this function to enable lane bonding of a
 * चयन. If conditions are correct and both चयनes support the feature,
 * lanes are bonded. It is safe to call this to any चयन.
 */
पूर्णांक tb_चयन_lane_bonding_enable(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_चयन *parent = tb_to_चयन(sw->dev.parent);
	काष्ठा tb_port *up, *करोwn;
	u64 route = tb_route(sw);
	पूर्णांक ret;

	अगर (!route)
		वापस 0;

	अगर (!tb_चयन_lane_bonding_possible(sw))
		वापस 0;

	up = tb_upstream_port(sw);
	करोwn = tb_port_at(route, parent);

	अगर (!tb_port_is_width_supported(up, 2) ||
	    !tb_port_is_width_supported(करोwn, 2))
		वापस 0;

	ret = tb_port_lane_bonding_enable(up);
	अगर (ret) अणु
		tb_port_warn(up, "failed to enable lane bonding\n");
		वापस ret;
	पूर्ण

	ret = tb_port_lane_bonding_enable(करोwn);
	अगर (ret) अणु
		tb_port_warn(करोwn, "failed to enable lane bonding\n");
		tb_port_lane_bonding_disable(up);
		वापस ret;
	पूर्ण

	tb_चयन_update_link_attributes(sw);

	tb_sw_dbg(sw, "lane bonding enabled\n");
	वापस ret;
पूर्ण

/**
 * tb_चयन_lane_bonding_disable() - Disable lane bonding
 * @sw: Switch whose lane bonding to disable
 *
 * Disables lane bonding between @sw and parent. This can be called even
 * अगर lanes were not bonded originally.
 */
व्योम tb_चयन_lane_bonding_disable(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_चयन *parent = tb_to_चयन(sw->dev.parent);
	काष्ठा tb_port *up, *करोwn;

	अगर (!tb_route(sw))
		वापस;

	up = tb_upstream_port(sw);
	अगर (!up->bonded)
		वापस;

	करोwn = tb_port_at(tb_route(sw), parent);

	tb_port_lane_bonding_disable(up);
	tb_port_lane_bonding_disable(करोwn);

	tb_चयन_update_link_attributes(sw);
	tb_sw_dbg(sw, "lane bonding disabled\n");
पूर्ण

/**
 * tb_चयन_configure_link() - Set link configured
 * @sw: Switch whose link is configured
 *
 * Sets the link upstream from @sw configured (from both ends) so that
 * it will not be disconnected when the करोमुख्य निकासs sleep. Can be
 * called क्रम any चयन.
 *
 * It is recommended that this is called after lane bonding is enabled.
 *
 * Returns %0 on success and negative त्रुटि_सं in हाल of error.
 */
पूर्णांक tb_चयन_configure_link(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *up, *करोwn;
	पूर्णांक ret;

	अगर (!tb_route(sw) || tb_चयन_is_icm(sw))
		वापस 0;

	up = tb_upstream_port(sw);
	अगर (tb_चयन_is_usb4(up->sw))
		ret = usb4_port_configure(up);
	अन्यथा
		ret = tb_lc_configure_port(up);
	अगर (ret)
		वापस ret;

	करोwn = up->remote;
	अगर (tb_चयन_is_usb4(करोwn->sw))
		वापस usb4_port_configure(करोwn);
	वापस tb_lc_configure_port(करोwn);
पूर्ण

/**
 * tb_चयन_unconfigure_link() - Unconfigure link
 * @sw: Switch whose link is unconfigured
 *
 * Sets the link unconfigured so the @sw will be disconnected अगर the
 * करोमुख्य exists sleep.
 */
व्योम tb_चयन_unconfigure_link(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *up, *करोwn;

	अगर (sw->is_unplugged)
		वापस;
	अगर (!tb_route(sw) || tb_चयन_is_icm(sw))
		वापस;

	up = tb_upstream_port(sw);
	अगर (tb_चयन_is_usb4(up->sw))
		usb4_port_unconfigure(up);
	अन्यथा
		tb_lc_unconfigure_port(up);

	करोwn = up->remote;
	अगर (tb_चयन_is_usb4(करोwn->sw))
		usb4_port_unconfigure(करोwn);
	अन्यथा
		tb_lc_unconfigure_port(करोwn);
पूर्ण

/**
 * tb_चयन_add() - Add a चयन to the करोमुख्य
 * @sw: Switch to add
 *
 * This is the last step in adding चयन to the करोमुख्य. It will पढ़ो
 * identअगरication inक्रमmation from DROM and initializes ports so that
 * they can be used to connect other चयनes. The चयन will be
 * exposed to the userspace when this function successfully वापसs. To
 * हटाओ and release the चयन, call tb_चयन_हटाओ().
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of failure
 */
पूर्णांक tb_चयन_add(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक i, ret;

	/*
	 * Initialize DMA control port now beक्रमe we पढ़ो DROM. Recent
	 * host controllers have more complete DROM on NVM that includes
	 * venकरोr and model identअगरication strings which we then expose
	 * to the userspace. NVM can be accessed through DMA
	 * configuration based mailbox.
	 */
	ret = tb_चयन_add_dma_port(sw);
	अगर (ret) अणु
		dev_err(&sw->dev, "failed to add DMA port\n");
		वापस ret;
	पूर्ण

	अगर (!sw->safe_mode) अणु
		/* पढ़ो drom */
		ret = tb_drom_पढ़ो(sw);
		अगर (ret) अणु
			dev_err(&sw->dev, "reading DROM failed\n");
			वापस ret;
		पूर्ण
		tb_sw_dbg(sw, "uid: %#llx\n", sw->uid);

		tb_check_quirks(sw);

		ret = tb_चयन_set_uuid(sw);
		अगर (ret) अणु
			dev_err(&sw->dev, "failed to set UUID\n");
			वापस ret;
		पूर्ण

		क्रम (i = 0; i <= sw->config.max_port_number; i++) अणु
			अगर (sw->ports[i].disabled) अणु
				tb_port_dbg(&sw->ports[i], "disabled by eeprom\n");
				जारी;
			पूर्ण
			ret = tb_init_port(&sw->ports[i]);
			अगर (ret) अणु
				dev_err(&sw->dev, "failed to initialize port %d\n", i);
				वापस ret;
			पूर्ण
		पूर्ण

		tb_चयन_शेष_link_ports(sw);

		ret = tb_चयन_update_link_attributes(sw);
		अगर (ret)
			वापस ret;

		ret = tb_चयन_पंचांगu_init(sw);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = device_add(&sw->dev);
	अगर (ret) अणु
		dev_err(&sw->dev, "failed to add device: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (tb_route(sw)) अणु
		dev_info(&sw->dev, "new device found, vendor=%#x device=%#x\n",
			 sw->venकरोr, sw->device);
		अगर (sw->venकरोr_name && sw->device_name)
			dev_info(&sw->dev, "%s %s\n", sw->venकरोr_name,
				 sw->device_name);
	पूर्ण

	ret = tb_चयन_nvm_add(sw);
	अगर (ret) अणु
		dev_err(&sw->dev, "failed to add NVM devices\n");
		device_del(&sw->dev);
		वापस ret;
	पूर्ण

	/*
	 * Thunderbolt routers करो not generate wakeups themselves but
	 * they क्रमward wakeups from tunneled protocols, so enable it
	 * here.
	 */
	device_init_wakeup(&sw->dev, true);

	pm_runसमय_set_active(&sw->dev);
	अगर (sw->rpm) अणु
		pm_runसमय_set_स्वतःsuspend_delay(&sw->dev, TB_AUTOSUSPEND_DELAY);
		pm_runसमय_use_स्वतःsuspend(&sw->dev);
		pm_runसमय_mark_last_busy(&sw->dev);
		pm_runसमय_enable(&sw->dev);
		pm_request_स्वतःsuspend(&sw->dev);
	पूर्ण

	tb_चयन_debugfs_init(sw);
	वापस 0;
पूर्ण

/**
 * tb_चयन_हटाओ() - Remove and release a चयन
 * @sw: Switch to हटाओ
 *
 * This will हटाओ the चयन from the करोमुख्य and release it after last
 * reference count drops to zero. If there are चयनes connected below
 * this चयन, they will be हटाओd as well.
 */
व्योम tb_चयन_हटाओ(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;

	tb_चयन_debugfs_हटाओ(sw);

	अगर (sw->rpm) अणु
		pm_runसमय_get_sync(&sw->dev);
		pm_runसमय_disable(&sw->dev);
	पूर्ण

	/* port 0 is the चयन itself and never has a remote */
	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_port_has_remote(port)) अणु
			tb_चयन_हटाओ(port->remote->sw);
			port->remote = शून्य;
		पूर्ण अन्यथा अगर (port->xकरोमुख्य) अणु
			tb_xकरोमुख्य_हटाओ(port->xकरोमुख्य);
			port->xकरोमुख्य = शून्य;
		पूर्ण

		/* Remove any करोwnstream reसमयrs */
		tb_reसमयr_हटाओ_all(port);
	पूर्ण

	अगर (!sw->is_unplugged)
		tb_plug_events_active(sw, false);

	tb_चयन_nvm_हटाओ(sw);

	अगर (tb_route(sw))
		dev_info(&sw->dev, "device disconnected\n");
	device_unरेजिस्टर(&sw->dev);
पूर्ण

/**
 * tb_sw_set_unplugged() - set is_unplugged on चयन and करोwnstream चयनes
 * @sw: Router to mark unplugged
 */
व्योम tb_sw_set_unplugged(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;

	अगर (sw == sw->tb->root_चयन) अणु
		tb_sw_WARN(sw, "cannot unplug root switch\n");
		वापस;
	पूर्ण
	अगर (sw->is_unplugged) अणु
		tb_sw_WARN(sw, "is_unplugged already set\n");
		वापस;
	पूर्ण
	sw->is_unplugged = true;
	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_port_has_remote(port))
			tb_sw_set_unplugged(port->remote->sw);
		अन्यथा अगर (port->xकरोमुख्य)
			port->xकरोमुख्य->is_unplugged = true;
	पूर्ण
पूर्ण

अटल पूर्णांक tb_चयन_set_wake(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags)
		tb_sw_dbg(sw, "enabling wakeup: %#x\n", flags);
	अन्यथा
		tb_sw_dbg(sw, "disabling wakeup\n");

	अगर (tb_चयन_is_usb4(sw))
		वापस usb4_चयन_set_wake(sw, flags);
	वापस tb_lc_set_wake(sw, flags);
पूर्ण

पूर्णांक tb_चयन_resume(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;
	पूर्णांक err;

	tb_sw_dbg(sw, "resuming switch\n");

	/*
	 * Check क्रम UID of the connected चयनes except क्रम root
	 * चयन which we assume cannot be हटाओd.
	 */
	अगर (tb_route(sw)) अणु
		u64 uid;

		/*
		 * Check first that we can still पढ़ो the चयन config
		 * space. It may be that there is now another करोमुख्य
		 * connected.
		 */
		err = tb_cfg_get_upstream_port(sw->tb->ctl, tb_route(sw));
		अगर (err < 0) अणु
			tb_sw_info(sw, "switch not present anymore\n");
			वापस err;
		पूर्ण

		अगर (tb_चयन_is_usb4(sw))
			err = usb4_चयन_पढ़ो_uid(sw, &uid);
		अन्यथा
			err = tb_drom_पढ़ो_uid_only(sw, &uid);
		अगर (err) अणु
			tb_sw_warn(sw, "uid read failed\n");
			वापस err;
		पूर्ण
		अगर (sw->uid != uid) अणु
			tb_sw_info(sw,
				"changed while suspended (uid %#llx -> %#llx)\n",
				sw->uid, uid);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	err = tb_चयन_configure(sw);
	अगर (err)
		वापस err;

	/* Disable wakes */
	tb_चयन_set_wake(sw, 0);

	err = tb_चयन_पंचांगu_init(sw);
	अगर (err)
		वापस err;

	/* check क्रम surviving करोwnstream चयनes */
	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!tb_port_has_remote(port) && !port->xकरोमुख्य) अणु
			/*
			 * For disconnected करोwnstream lane adapters
			 * start lane initialization now so we detect
			 * future connects.
			 */
			अगर (!tb_is_upstream_port(port) && tb_port_is_null(port))
				tb_port_start_lane_initialization(port);
			जारी;
		पूर्ण अन्यथा अगर (port->xकरोमुख्य) अणु
			/*
			 * Start lane initialization क्रम XDoमुख्य so the
			 * link माला_लो re-established.
			 */
			tb_port_start_lane_initialization(port);
		पूर्ण

		अगर (tb_रुको_क्रम_port(port, true) <= 0) अणु
			tb_port_warn(port,
				     "lost during suspend, disconnecting\n");
			अगर (tb_port_has_remote(port))
				tb_sw_set_unplugged(port->remote->sw);
			अन्यथा अगर (port->xकरोमुख्य)
				port->xकरोमुख्य->is_unplugged = true;
		पूर्ण अन्यथा अगर (tb_port_has_remote(port) || port->xकरोमुख्य) अणु
			/*
			 * Always unlock the port so the करोwnstream
			 * चयन/करोमुख्य is accessible.
			 */
			अगर (tb_port_unlock(port))
				tb_port_warn(port, "failed to unlock port\n");
			अगर (port->remote && tb_चयन_resume(port->remote->sw)) अणु
				tb_port_warn(port,
					     "lost during suspend, disconnecting\n");
				tb_sw_set_unplugged(port->remote->sw);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * tb_चयन_suspend() - Put a चयन to sleep
 * @sw: Switch to suspend
 * @runसमय: Is this runसमय suspend or प्रणाली sleep
 *
 * Suspends router and all its children. Enables wakes according to
 * value of @runसमय and then sets sleep bit क्रम the router. If @sw is
 * host router the करोमुख्य is पढ़ोy to go to sleep once this function
 * वापसs.
 */
व्योम tb_चयन_suspend(काष्ठा tb_चयन *sw, bool runसमय)
अणु
	अचिन्हित पूर्णांक flags = 0;
	काष्ठा tb_port *port;
	पूर्णांक err;

	tb_sw_dbg(sw, "suspending switch\n");

	err = tb_plug_events_active(sw, false);
	अगर (err)
		वापस;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_port_has_remote(port))
			tb_चयन_suspend(port->remote->sw, runसमय);
	पूर्ण

	अगर (runसमय) अणु
		/* Trigger wake when something is plugged in/out */
		flags |= TB_WAKE_ON_CONNECT | TB_WAKE_ON_DISCONNECT;
		flags |= TB_WAKE_ON_USB4 | TB_WAKE_ON_USB3 | TB_WAKE_ON_PCIE;
	पूर्ण अन्यथा अगर (device_may_wakeup(&sw->dev)) अणु
		flags |= TB_WAKE_ON_USB4 | TB_WAKE_ON_USB3 | TB_WAKE_ON_PCIE;
	पूर्ण

	tb_चयन_set_wake(sw, flags);

	अगर (tb_चयन_is_usb4(sw))
		usb4_चयन_set_sleep(sw);
	अन्यथा
		tb_lc_set_sleep(sw);
पूर्ण

/**
 * tb_चयन_query_dp_resource() - Query availability of DP resource
 * @sw: Switch whose DP resource is queried
 * @in: DP IN port
 *
 * Queries availability of DP resource क्रम DP tunneling using चयन
 * specअगरic means. Returns %true अगर resource is available.
 */
bool tb_चयन_query_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	अगर (tb_चयन_is_usb4(sw))
		वापस usb4_चयन_query_dp_resource(sw, in);
	वापस tb_lc_dp_sink_query(sw, in);
पूर्ण

/**
 * tb_चयन_alloc_dp_resource() - Allocate available DP resource
 * @sw: Switch whose DP resource is allocated
 * @in: DP IN port
 *
 * Allocates DP resource क्रम DP tunneling. The resource must be
 * available क्रम this to succeed (see tb_चयन_query_dp_resource()).
 * Returns %0 in success and negative त्रुटि_सं otherwise.
 */
पूर्णांक tb_चयन_alloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	अगर (tb_चयन_is_usb4(sw))
		वापस usb4_चयन_alloc_dp_resource(sw, in);
	वापस tb_lc_dp_sink_alloc(sw, in);
पूर्ण

/**
 * tb_चयन_dealloc_dp_resource() - De-allocate DP resource
 * @sw: Switch whose DP resource is de-allocated
 * @in: DP IN port
 *
 * De-allocates DP resource that was previously allocated क्रम DP
 * tunneling.
 */
व्योम tb_चयन_dealloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	पूर्णांक ret;

	अगर (tb_चयन_is_usb4(sw))
		ret = usb4_चयन_dealloc_dp_resource(sw, in);
	अन्यथा
		ret = tb_lc_dp_sink_dealloc(sw, in);

	अगर (ret)
		tb_sw_warn(sw, "failed to de-allocate DP resource for port %d\n",
			   in->port);
पूर्ण

काष्ठा tb_sw_lookup अणु
	काष्ठा tb *tb;
	u8 link;
	u8 depth;
	स्थिर uuid_t *uuid;
	u64 route;
पूर्ण;

अटल पूर्णांक tb_चयन_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);
	स्थिर काष्ठा tb_sw_lookup *lookup = data;

	अगर (!sw)
		वापस 0;
	अगर (sw->tb != lookup->tb)
		वापस 0;

	अगर (lookup->uuid)
		वापस !स_भेद(sw->uuid, lookup->uuid, माप(*lookup->uuid));

	अगर (lookup->route) अणु
		वापस sw->config.route_lo == lower_32_bits(lookup->route) &&
		       sw->config.route_hi == upper_32_bits(lookup->route);
	पूर्ण

	/* Root चयन is matched only by depth */
	अगर (!lookup->depth)
		वापस !sw->depth;

	वापस sw->link == lookup->link && sw->depth == lookup->depth;
पूर्ण

/**
 * tb_चयन_find_by_link_depth() - Find चयन by link and depth
 * @tb: Doमुख्य the चयन beदीर्घs
 * @link: Link number the चयन is connected
 * @depth: Depth of the चयन in link
 *
 * Returned चयन has reference count increased so the caller needs to
 * call tb_चयन_put() when करोne with the चयन.
 */
काष्ठा tb_चयन *tb_चयन_find_by_link_depth(काष्ठा tb *tb, u8 link, u8 depth)
अणु
	काष्ठा tb_sw_lookup lookup;
	काष्ठा device *dev;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.tb = tb;
	lookup.link = link;
	lookup.depth = depth;

	dev = bus_find_device(&tb_bus_type, शून्य, &lookup, tb_चयन_match);
	अगर (dev)
		वापस tb_to_चयन(dev);

	वापस शून्य;
पूर्ण

/**
 * tb_चयन_find_by_uuid() - Find चयन by UUID
 * @tb: Doमुख्य the चयन beदीर्घs
 * @uuid: UUID to look क्रम
 *
 * Returned चयन has reference count increased so the caller needs to
 * call tb_चयन_put() when करोne with the चयन.
 */
काष्ठा tb_चयन *tb_चयन_find_by_uuid(काष्ठा tb *tb, स्थिर uuid_t *uuid)
अणु
	काष्ठा tb_sw_lookup lookup;
	काष्ठा device *dev;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.tb = tb;
	lookup.uuid = uuid;

	dev = bus_find_device(&tb_bus_type, शून्य, &lookup, tb_चयन_match);
	अगर (dev)
		वापस tb_to_चयन(dev);

	वापस शून्य;
पूर्ण

/**
 * tb_चयन_find_by_route() - Find चयन by route string
 * @tb: Doमुख्य the चयन beदीर्घs
 * @route: Route string to look क्रम
 *
 * Returned चयन has reference count increased so the caller needs to
 * call tb_चयन_put() when करोne with the चयन.
 */
काष्ठा tb_चयन *tb_चयन_find_by_route(काष्ठा tb *tb, u64 route)
अणु
	काष्ठा tb_sw_lookup lookup;
	काष्ठा device *dev;

	अगर (!route)
		वापस tb_चयन_get(tb->root_चयन);

	स_रखो(&lookup, 0, माप(lookup));
	lookup.tb = tb;
	lookup.route = route;

	dev = bus_find_device(&tb_bus_type, शून्य, &lookup, tb_चयन_match);
	अगर (dev)
		वापस tb_to_चयन(dev);

	वापस शून्य;
पूर्ण

/**
 * tb_चयन_find_port() - वापस the first port of @type on @sw or शून्य
 * @sw: Switch to find the port from
 * @type: Port type to look क्रम
 */
काष्ठा tb_port *tb_चयन_find_port(काष्ठा tb_चयन *sw,
				    क्रमागत tb_port_type type)
अणु
	काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (port->config.type == type)
			वापस port;
	पूर्ण

	वापस शून्य;
पूर्ण
