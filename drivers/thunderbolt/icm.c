<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Internal Thunderbolt Connection Manager. This is a firmware running on
 * the Thunderbolt host controller perक्रमming most of the low-level
 * handling.
 *
 * Copyright (C) 2017, Intel Corporation
 * Authors: Michael Jamet <michael.jamet@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "ctl.h"
#समावेश "nhi_regs.h"
#समावेश "tb.h"

#घोषणा PCIE2CIO_CMD			0x30
#घोषणा PCIE2CIO_CMD_TIMEOUT		BIT(31)
#घोषणा PCIE2CIO_CMD_START		BIT(30)
#घोषणा PCIE2CIO_CMD_WRITE		BIT(21)
#घोषणा PCIE2CIO_CMD_CS_MASK		GENMASK(20, 19)
#घोषणा PCIE2CIO_CMD_CS_SHIFT		19
#घोषणा PCIE2CIO_CMD_PORT_MASK		GENMASK(18, 13)
#घोषणा PCIE2CIO_CMD_PORT_SHIFT		13

#घोषणा PCIE2CIO_WRDATA			0x34
#घोषणा PCIE2CIO_RDDATA			0x38

#घोषणा PHY_PORT_CS1			0x37
#घोषणा PHY_PORT_CS1_LINK_DISABLE	BIT(14)
#घोषणा PHY_PORT_CS1_LINK_STATE_MASK	GENMASK(29, 26)
#घोषणा PHY_PORT_CS1_LINK_STATE_SHIFT	26

#घोषणा ICM_TIMEOUT			5000	/* ms */
#घोषणा ICM_APPROVE_TIMEOUT		10000	/* ms */
#घोषणा ICM_MAX_LINK			4

अटल bool start_icm;
module_param(start_icm, bool, 0444);
MODULE_PARM_DESC(start_icm, "start ICM firmware if it is not running (default: false)");

/**
 * काष्ठा usb4_चयन_nvm_auth - Holds USB4 NVM_AUTH status
 * @reply: Reply from ICM firmware is placed here
 * @request: Request that is sent to ICM firmware
 * @icm: Poपूर्णांकer to ICM निजी data
 */
काष्ठा usb4_चयन_nvm_auth अणु
	काष्ठा icm_usb4_चयन_op_response reply;
	काष्ठा icm_usb4_चयन_op request;
	काष्ठा icm *icm;
पूर्ण;

/**
 * काष्ठा icm - Internal connection manager निजी data
 * @request_lock: Makes sure only one message is send to ICM at समय
 * @rescan_work: Work used to rescan the surviving चयनes after resume
 * @upstream_port: Poपूर्णांकer to the PCIe upstream port this host
 *		   controller is connected. This is only set क्रम प्रणालीs
 *		   where ICM needs to be started manually
 * @vnd_cap: Venकरोr defined capability where PCIe2CIO mailbox resides
 *	     (only set when @upstream_port is not %शून्य)
 * @safe_mode: ICM is in safe mode
 * @max_boot_acl: Maximum number of preboot ACL entries (%0 अगर not supported)
 * @rpm: Does the controller support runसमय PM (RTD3)
 * @can_upgrade_nvm: Can the NVM firmware be upgrade on this controller
 * @proto_version: Firmware protocol version
 * @last_nvm_auth: Last USB4 router NVM_AUTH result (or %शून्य अगर not set)
 * @veto: Is RTD3 veto in effect
 * @is_supported: Checks अगर we can support ICM on this controller
 * @cio_reset: Trigger CIO reset
 * @get_mode: Read and वापस the ICM firmware mode (optional)
 * @get_route: Find a route string क्रम given चयन
 * @save_devices: Ask ICM to save devices to ACL when suspending (optional)
 * @driver_पढ़ोy: Send driver पढ़ोy message to ICM
 * @set_uuid: Set UUID क्रम the root चयन (optional)
 * @device_connected: Handle device connected ICM message
 * @device_disconnected: Handle device disconnected ICM message
 * @xकरोमुख्य_connected: Handle XDoमुख्य connected ICM message
 * @xकरोमुख्य_disconnected: Handle XDoमुख्य disconnected ICM message
 * @rtd3_veto: Handle RTD3 veto notअगरication ICM message
 */
काष्ठा icm अणु
	काष्ठा mutex request_lock;
	काष्ठा delayed_work rescan_work;
	काष्ठा pci_dev *upstream_port;
	पूर्णांक vnd_cap;
	bool safe_mode;
	माप_प्रकार max_boot_acl;
	bool rpm;
	bool can_upgrade_nvm;
	u8 proto_version;
	काष्ठा usb4_चयन_nvm_auth *last_nvm_auth;
	bool veto;
	bool (*is_supported)(काष्ठा tb *tb);
	पूर्णांक (*cio_reset)(काष्ठा tb *tb);
	पूर्णांक (*get_mode)(काष्ठा tb *tb);
	पूर्णांक (*get_route)(काष्ठा tb *tb, u8 link, u8 depth, u64 *route);
	व्योम (*save_devices)(काष्ठा tb *tb);
	पूर्णांक (*driver_पढ़ोy)(काष्ठा tb *tb,
			    क्रमागत tb_security_level *security_level,
			    u8 *proto_version, माप_प्रकार *nboot_acl, bool *rpm);
	व्योम (*set_uuid)(काष्ठा tb *tb);
	व्योम (*device_connected)(काष्ठा tb *tb,
				 स्थिर काष्ठा icm_pkg_header *hdr);
	व्योम (*device_disconnected)(काष्ठा tb *tb,
				    स्थिर काष्ठा icm_pkg_header *hdr);
	व्योम (*xकरोमुख्य_connected)(काष्ठा tb *tb,
				  स्थिर काष्ठा icm_pkg_header *hdr);
	व्योम (*xकरोमुख्य_disconnected)(काष्ठा tb *tb,
				     स्थिर काष्ठा icm_pkg_header *hdr);
	व्योम (*rtd3_veto)(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr);
पूर्ण;

काष्ठा icm_notअगरication अणु
	काष्ठा work_काष्ठा work;
	काष्ठा icm_pkg_header *pkg;
	काष्ठा tb *tb;
पूर्ण;

काष्ठा ep_name_entry अणु
	u8 len;
	u8 type;
	u8 data[];
पूर्ण;

#घोषणा EP_NAME_INTEL_VSS	0x10

/* Intel Venकरोr specअगरic काष्ठाure */
काष्ठा पूर्णांकel_vss अणु
	u16 venकरोr;
	u16 model;
	u8 mc;
	u8 flags;
	u16 pci_devid;
	u32 nvm_version;
पूर्ण;

#घोषणा INTEL_VSS_FLAGS_RTD3	BIT(0)

अटल स्थिर काष्ठा पूर्णांकel_vss *parse_पूर्णांकel_vss(स्थिर व्योम *ep_name, माप_प्रकार size)
अणु
	स्थिर व्योम *end = ep_name + size;

	जबतक (ep_name < end) अणु
		स्थिर काष्ठा ep_name_entry *ep = ep_name;

		अगर (!ep->len)
			अवरोध;
		अगर (ep_name + ep->len > end)
			अवरोध;

		अगर (ep->type == EP_NAME_INTEL_VSS)
			वापस (स्थिर काष्ठा पूर्णांकel_vss *)ep->data;

		ep_name += ep->len;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool पूर्णांकel_vss_is_rtd3(स्थिर व्योम *ep_name, माप_प्रकार size)
अणु
	स्थिर काष्ठा पूर्णांकel_vss *vss;

	vss = parse_पूर्णांकel_vss(ep_name, size);
	अगर (vss)
		वापस !!(vss->flags & INTEL_VSS_FLAGS_RTD3);

	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा tb *icm_to_tb(काष्ठा icm *icm)
अणु
	वापस ((व्योम *)icm - माप(काष्ठा tb));
पूर्ण

अटल अंतरभूत u8 phy_port_from_route(u64 route, u8 depth)
अणु
	u8 link;

	link = depth ? route >> ((depth - 1) * 8) : route;
	वापस tb_phy_port_from_link(link);
पूर्ण

अटल अंतरभूत u8 dual_link_from_link(u8 link)
अणु
	वापस link ? ((link - 1) ^ 0x01) + 1 : 0;
पूर्ण

अटल अंतरभूत u64 get_route(u32 route_hi, u32 route_lo)
अणु
	वापस (u64)route_hi << 32 | route_lo;
पूर्ण

अटल अंतरभूत u64 get_parent_route(u64 route)
अणु
	पूर्णांक depth = tb_route_length(route);
	वापस depth ? route & ~(0xffULL << (depth - 1) * TB_ROUTE_SHIFT) : 0;
पूर्ण

अटल पूर्णांक pci2cio_रुको_completion(काष्ठा icm *icm, अचिन्हित दीर्घ समयout_msec)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(समयout_msec);
	u32 cmd;

	करो अणु
		pci_पढ़ो_config_dword(icm->upstream_port,
				      icm->vnd_cap + PCIE2CIO_CMD, &cmd);
		अगर (!(cmd & PCIE2CIO_CMD_START)) अणु
			अगर (cmd & PCIE2CIO_CMD_TIMEOUT)
				अवरोध;
			वापस 0;
		पूर्ण

		msleep(50);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक pcie2cio_पढ़ो(काष्ठा icm *icm, क्रमागत tb_cfg_space cs,
			 अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक index, u32 *data)
अणु
	काष्ठा pci_dev *pdev = icm->upstream_port;
	पूर्णांक ret, vnd_cap = icm->vnd_cap;
	u32 cmd;

	cmd = index;
	cmd |= (port << PCIE2CIO_CMD_PORT_SHIFT) & PCIE2CIO_CMD_PORT_MASK;
	cmd |= (cs << PCIE2CIO_CMD_CS_SHIFT) & PCIE2CIO_CMD_CS_MASK;
	cmd |= PCIE2CIO_CMD_START;
	pci_ग_लिखो_config_dword(pdev, vnd_cap + PCIE2CIO_CMD, cmd);

	ret = pci2cio_रुको_completion(icm, 5000);
	अगर (ret)
		वापस ret;

	pci_पढ़ो_config_dword(pdev, vnd_cap + PCIE2CIO_RDDATA, data);
	वापस 0;
पूर्ण

अटल पूर्णांक pcie2cio_ग_लिखो(काष्ठा icm *icm, क्रमागत tb_cfg_space cs,
			  अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक index, u32 data)
अणु
	काष्ठा pci_dev *pdev = icm->upstream_port;
	पूर्णांक vnd_cap = icm->vnd_cap;
	u32 cmd;

	pci_ग_लिखो_config_dword(pdev, vnd_cap + PCIE2CIO_WRDATA, data);

	cmd = index;
	cmd |= (port << PCIE2CIO_CMD_PORT_SHIFT) & PCIE2CIO_CMD_PORT_MASK;
	cmd |= (cs << PCIE2CIO_CMD_CS_SHIFT) & PCIE2CIO_CMD_CS_MASK;
	cmd |= PCIE2CIO_CMD_WRITE | PCIE2CIO_CMD_START;
	pci_ग_लिखो_config_dword(pdev, vnd_cap + PCIE2CIO_CMD, cmd);

	वापस pci2cio_रुको_completion(icm, 5000);
पूर्ण

अटल bool icm_match(स्थिर काष्ठा tb_cfg_request *req,
		      स्थिर काष्ठा ctl_pkg *pkg)
अणु
	स्थिर काष्ठा icm_pkg_header *res_hdr = pkg->buffer;
	स्थिर काष्ठा icm_pkg_header *req_hdr = req->request;

	अगर (pkg->frame.eof != req->response_type)
		वापस false;
	अगर (res_hdr->code != req_hdr->code)
		वापस false;

	वापस true;
पूर्ण

अटल bool icm_copy(काष्ठा tb_cfg_request *req, स्थिर काष्ठा ctl_pkg *pkg)
अणु
	स्थिर काष्ठा icm_pkg_header *hdr = pkg->buffer;

	अगर (hdr->packet_id < req->npackets) अणु
		माप_प्रकार offset = hdr->packet_id * req->response_size;

		स_नकल(req->response + offset, pkg->buffer, req->response_size);
	पूर्ण

	वापस hdr->packet_id == hdr->total_packets - 1;
पूर्ण

अटल पूर्णांक icm_request(काष्ठा tb *tb, स्थिर व्योम *request, माप_प्रकार request_size,
		       व्योम *response, माप_प्रकार response_size, माप_प्रकार npackets,
		       अचिन्हित पूर्णांक समयout_msec)
अणु
	काष्ठा icm *icm = tb_priv(tb);
	पूर्णांक retries = 3;

	करो अणु
		काष्ठा tb_cfg_request *req;
		काष्ठा tb_cfg_result res;

		req = tb_cfg_request_alloc();
		अगर (!req)
			वापस -ENOMEM;

		req->match = icm_match;
		req->copy = icm_copy;
		req->request = request;
		req->request_size = request_size;
		req->request_type = TB_CFG_PKG_ICM_CMD;
		req->response = response;
		req->npackets = npackets;
		req->response_size = response_size;
		req->response_type = TB_CFG_PKG_ICM_RESP;

		mutex_lock(&icm->request_lock);
		res = tb_cfg_request_sync(tb->ctl, req, समयout_msec);
		mutex_unlock(&icm->request_lock);

		tb_cfg_request_put(req);

		अगर (res.err != -ETIMEDOUT)
			वापस res.err == 1 ? -EIO : res.err;

		usleep_range(20, 50);
	पूर्ण जबतक (retries--);

	वापस -ETIMEDOUT;
पूर्ण

/*
 * If rescan is queued to run (we are resuming), postpone it to give the
 * firmware some more समय to send device connected notअगरications क्रम next
 * devices in the chain.
 */
अटल व्योम icm_postpone_rescan(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);

	अगर (delayed_work_pending(&icm->rescan_work))
		mod_delayed_work(tb->wq, &icm->rescan_work,
				 msecs_to_jअगरfies(500));
पूर्ण

अटल व्योम icm_veto_begin(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);

	अगर (!icm->veto) अणु
		icm->veto = true;
		/* Keep the करोमुख्य घातered जबतक veto is in effect */
		pm_runसमय_get(&tb->dev);
	पूर्ण
पूर्ण

अटल व्योम icm_veto_end(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);

	अगर (icm->veto) अणु
		icm->veto = false;
		/* Allow the करोमुख्य suspend now */
		pm_runसमय_mark_last_busy(&tb->dev);
		pm_runसमय_put_स्वतःsuspend(&tb->dev);
	पूर्ण
पूर्ण

अटल bool icm_firmware_running(स्थिर काष्ठा tb_nhi *nhi)
अणु
	u32 val;

	val = ioपढ़ो32(nhi->iobase + REG_FW_STS);
	वापस !!(val & REG_FW_STS_ICM_EN);
पूर्ण

अटल bool icm_fr_is_supported(काष्ठा tb *tb)
अणु
	वापस !x86_apple_machine;
पूर्ण

अटल अंतरभूत पूर्णांक icm_fr_get_चयन_index(u32 port)
अणु
	पूर्णांक index;

	अगर ((port & ICM_PORT_TYPE_MASK) != TB_TYPE_PORT)
		वापस 0;

	index = port >> ICM_PORT_INDEX_SHIFT;
	वापस index != 0xff ? index : 0;
पूर्ण

अटल पूर्णांक icm_fr_get_route(काष्ठा tb *tb, u8 link, u8 depth, u64 *route)
अणु
	काष्ठा icm_fr_pkg_get_topology_response *चयनes, *sw;
	काष्ठा icm_fr_pkg_get_topology request = अणु
		.hdr = अणु .code = ICM_GET_TOPOLOGY पूर्ण,
	पूर्ण;
	माप_प्रकार npackets = ICM_GET_TOPOLOGY_PACKETS;
	पूर्णांक ret, index;
	u8 i;

	चयनes = kसुस्मृति(npackets, माप(*चयनes), GFP_KERNEL);
	अगर (!चयनes)
		वापस -ENOMEM;

	ret = icm_request(tb, &request, माप(request), चयनes,
			  माप(*चयनes), npackets, ICM_TIMEOUT);
	अगर (ret)
		जाओ err_मुक्त;

	sw = &चयनes[0];
	index = icm_fr_get_चयन_index(sw->ports[link]);
	अगर (!index) अणु
		ret = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	sw = &चयनes[index];
	क्रम (i = 1; i < depth; i++) अणु
		अचिन्हित पूर्णांक j;

		अगर (!(sw->first_data & ICM_SWITCH_USED)) अणु
			ret = -ENODEV;
			जाओ err_मुक्त;
		पूर्ण

		क्रम (j = 0; j < ARRAY_SIZE(sw->ports); j++) अणु
			index = icm_fr_get_चयन_index(sw->ports[j]);
			अगर (index > sw->चयन_index) अणु
				sw = &चयनes[index];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	*route = get_route(sw->route_hi, sw->route_lo);

err_मुक्त:
	kमुक्त(चयनes);
	वापस ret;
पूर्ण

अटल व्योम icm_fr_save_devices(काष्ठा tb *tb)
अणु
	nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_SAVE_DEVS, 0);
पूर्ण

अटल पूर्णांक
icm_fr_driver_पढ़ोy(काष्ठा tb *tb, क्रमागत tb_security_level *security_level,
		    u8 *proto_version, माप_प्रकार *nboot_acl, bool *rpm)
अणु
	काष्ठा icm_fr_pkg_driver_पढ़ोy_response reply;
	काष्ठा icm_pkg_driver_पढ़ोy request = अणु
		.hdr.code = ICM_DRIVER_READY,
	पूर्ण;
	पूर्णांक ret;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (security_level)
		*security_level = reply.security_level & ICM_FR_SLEVEL_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक icm_fr_approve_चयन(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा icm_fr_pkg_approve_device request;
	काष्ठा icm_fr_pkg_approve_device reply;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	स_नकल(&request.ep_uuid, sw->uuid, माप(request.ep_uuid));
	request.hdr.code = ICM_APPROVE_DEVICE;
	request.connection_id = sw->connection_id;
	request.connection_key = sw->connection_key;

	स_रखो(&reply, 0, माप(reply));
	/* Use larger समयout as establishing tunnels can take some समय */
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_APPROVE_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR) अणु
		tb_warn(tb, "PCIe tunnel creation failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icm_fr_add_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा icm_fr_pkg_add_device_key request;
	काष्ठा icm_fr_pkg_add_device_key_response reply;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	स_नकल(&request.ep_uuid, sw->uuid, माप(request.ep_uuid));
	request.hdr.code = ICM_ADD_DEVICE_KEY;
	request.connection_id = sw->connection_id;
	request.connection_key = sw->connection_key;
	स_नकल(request.key, sw->key, TB_SWITCH_KEY_SIZE);

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR) अणु
		tb_warn(tb, "Adding key to switch failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icm_fr_challenge_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw,
				       स्थिर u8 *challenge, u8 *response)
अणु
	काष्ठा icm_fr_pkg_challenge_device request;
	काष्ठा icm_fr_pkg_challenge_device_response reply;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	स_नकल(&request.ep_uuid, sw->uuid, माप(request.ep_uuid));
	request.hdr.code = ICM_CHALLENGE_DEVICE;
	request.connection_id = sw->connection_id;
	request.connection_key = sw->connection_key;
	स_नकल(request.challenge, challenge, TB_SWITCH_KEY_SIZE);

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EKEYREJECTED;
	अगर (reply.hdr.flags & ICM_FLAGS_NO_KEY)
		वापस -ENOKEY;

	स_नकल(response, reply.response, TB_SWITCH_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक icm_fr_approve_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
					पूर्णांक transmit_path, पूर्णांक transmit_ring,
					पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	काष्ठा icm_fr_pkg_approve_xकरोमुख्य_response reply;
	काष्ठा icm_fr_pkg_approve_xकरोमुख्य request;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	request.hdr.code = ICM_APPROVE_XDOMAIN;
	request.link_info = xd->depth << ICM_LINK_INFO_DEPTH_SHIFT | xd->link;
	स_नकल(&request.remote_uuid, xd->remote_uuid, माप(*xd->remote_uuid));

	request.transmit_path = transmit_path;
	request.transmit_ring = transmit_ring;
	request.receive_path = receive_path;
	request.receive_ring = receive_ring;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक icm_fr_disconnect_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
					   पूर्णांक transmit_path, पूर्णांक transmit_ring,
					   पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	u8 phy_port;
	u8 cmd;

	phy_port = tb_phy_port_from_link(xd->link);
	अगर (phy_port == 0)
		cmd = NHI_MAILBOX_DISCONNECT_PA;
	अन्यथा
		cmd = NHI_MAILBOX_DISCONNECT_PB;

	nhi_mailbox_cmd(tb->nhi, cmd, 1);
	usleep_range(10, 50);
	nhi_mailbox_cmd(tb->nhi, cmd, 2);
	वापस 0;
पूर्ण

अटल काष्ठा tb_चयन *alloc_चयन(काष्ठा tb_चयन *parent_sw, u64 route,
				      स्थिर uuid_t *uuid)
अणु
	काष्ठा tb *tb = parent_sw->tb;
	काष्ठा tb_चयन *sw;

	sw = tb_चयन_alloc(tb, &parent_sw->dev, route);
	अगर (IS_ERR(sw)) अणु
		tb_warn(tb, "failed to allocate switch at %llx\n", route);
		वापस sw;
	पूर्ण

	sw->uuid = kmemdup(uuid, माप(*uuid), GFP_KERNEL);
	अगर (!sw->uuid) अणु
		tb_चयन_put(sw);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	init_completion(&sw->rpm_complete);
	वापस sw;
पूर्ण

अटल पूर्णांक add_चयन(काष्ठा tb_चयन *parent_sw, काष्ठा tb_चयन *sw)
अणु
	u64 route = tb_route(sw);
	पूर्णांक ret;

	/* Link the two चयनes now */
	tb_port_at(route, parent_sw)->remote = tb_upstream_port(sw);
	tb_upstream_port(sw)->remote = tb_port_at(route, parent_sw);

	ret = tb_चयन_add(sw);
	अगर (ret)
		tb_port_at(tb_route(sw), parent_sw)->remote = शून्य;

	वापस ret;
पूर्ण

अटल व्योम update_चयन(काष्ठा tb_चयन *parent_sw, काष्ठा tb_चयन *sw,
			  u64 route, u8 connection_id, u8 connection_key,
			  u8 link, u8 depth, bool boot)
अणु
	/* Disconnect from parent */
	tb_port_at(tb_route(sw), parent_sw)->remote = शून्य;
	/* Re-connect via updated port*/
	tb_port_at(route, parent_sw)->remote = tb_upstream_port(sw);

	/* Update with the new addressing inक्रमmation */
	sw->config.route_hi = upper_32_bits(route);
	sw->config.route_lo = lower_32_bits(route);
	sw->connection_id = connection_id;
	sw->connection_key = connection_key;
	sw->link = link;
	sw->depth = depth;
	sw->boot = boot;

	/* This चयन still exists */
	sw->is_unplugged = false;

	/* Runसमय resume is now complete */
	complete(&sw->rpm_complete);
पूर्ण

अटल व्योम हटाओ_चयन(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_चयन *parent_sw;

	parent_sw = tb_to_चयन(sw->dev.parent);
	tb_port_at(tb_route(sw), parent_sw)->remote = शून्य;
	tb_चयन_हटाओ(sw);
पूर्ण

अटल व्योम add_xकरोमुख्य(काष्ठा tb_चयन *sw, u64 route,
			स्थिर uuid_t *local_uuid, स्थिर uuid_t *remote_uuid,
			u8 link, u8 depth)
अणु
	काष्ठा tb_xकरोमुख्य *xd;

	pm_runसमय_get_sync(&sw->dev);

	xd = tb_xकरोमुख्य_alloc(sw->tb, &sw->dev, route, local_uuid, remote_uuid);
	अगर (!xd)
		जाओ out;

	xd->link = link;
	xd->depth = depth;

	tb_port_at(route, sw)->xकरोमुख्य = xd;

	tb_xकरोमुख्य_add(xd);

out:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);
पूर्ण

अटल व्योम update_xकरोमुख्य(काष्ठा tb_xकरोमुख्य *xd, u64 route, u8 link)
अणु
	xd->link = link;
	xd->route = route;
	xd->is_unplugged = false;
पूर्ण

अटल व्योम हटाओ_xकरोमुख्य(काष्ठा tb_xकरोमुख्य *xd)
अणु
	काष्ठा tb_चयन *sw;

	sw = tb_to_चयन(xd->dev.parent);
	tb_port_at(xd->route, sw)->xकरोमुख्य = शून्य;
	tb_xकरोमुख्य_हटाओ(xd);
पूर्ण

अटल व्योम
icm_fr_device_connected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_fr_event_device_connected *pkg =
		(स्थिर काष्ठा icm_fr_event_device_connected *)hdr;
	क्रमागत tb_security_level security_level;
	काष्ठा tb_चयन *sw, *parent_sw;
	bool boot, dual_lane, speed_gen3;
	काष्ठा icm *icm = tb_priv(tb);
	bool authorized = false;
	काष्ठा tb_xकरोमुख्य *xd;
	u8 link, depth;
	u64 route;
	पूर्णांक ret;

	icm_postpone_rescan(tb);

	link = pkg->link_info & ICM_LINK_INFO_LINK_MASK;
	depth = (pkg->link_info & ICM_LINK_INFO_DEPTH_MASK) >>
		ICM_LINK_INFO_DEPTH_SHIFT;
	authorized = pkg->link_info & ICM_LINK_INFO_APPROVED;
	security_level = (pkg->hdr.flags & ICM_FLAGS_SLEVEL_MASK) >>
			 ICM_FLAGS_SLEVEL_SHIFT;
	boot = pkg->link_info & ICM_LINK_INFO_BOOT;
	dual_lane = pkg->hdr.flags & ICM_FLAGS_DUAL_LANE;
	speed_gen3 = pkg->hdr.flags & ICM_FLAGS_SPEED_GEN3;

	अगर (pkg->link_info & ICM_LINK_INFO_REJECTED) अणु
		tb_info(tb, "switch at %u.%u was rejected by ICM firmware because topology limit exceeded\n",
			link, depth);
		वापस;
	पूर्ण

	sw = tb_चयन_find_by_uuid(tb, &pkg->ep_uuid);
	अगर (sw) अणु
		u8 phy_port, sw_phy_port;

		parent_sw = tb_to_चयन(sw->dev.parent);
		sw_phy_port = tb_phy_port_from_link(sw->link);
		phy_port = tb_phy_port_from_link(link);

		/*
		 * On resume ICM will send us connected events क्रम the
		 * devices that still are present. However, that
		 * inक्रमmation might have changed क्रम example by the
		 * fact that a चयन on a dual-link connection might
		 * have been क्रमागतerated using the other link now. Make
		 * sure our book keeping matches that.
		 */
		अगर (sw->depth == depth && sw_phy_port == phy_port &&
		    !!sw->authorized == authorized) अणु
			/*
			 * It was क्रमागतerated through another link so update
			 * route string accordingly.
			 */
			अगर (sw->link != link) अणु
				ret = icm->get_route(tb, link, depth, &route);
				अगर (ret) अणु
					tb_err(tb, "failed to update route string for switch at %u.%u\n",
					       link, depth);
					tb_चयन_put(sw);
					वापस;
				पूर्ण
			पूर्ण अन्यथा अणु
				route = tb_route(sw);
			पूर्ण

			update_चयन(parent_sw, sw, route, pkg->connection_id,
				      pkg->connection_key, link, depth, boot);
			tb_चयन_put(sw);
			वापस;
		पूर्ण

		/*
		 * User connected the same चयन to another physical
		 * port or to another part of the topology. Remove the
		 * existing चयन now beक्रमe adding the new one.
		 */
		हटाओ_चयन(sw);
		tb_चयन_put(sw);
	पूर्ण

	/*
	 * If the चयन was not found by UUID, look क्रम a चयन on
	 * same physical port (taking possible link aggregation पूर्णांकo
	 * account) and depth. If we found one it is definitely a stale
	 * one so हटाओ it first.
	 */
	sw = tb_चयन_find_by_link_depth(tb, link, depth);
	अगर (!sw) अणु
		u8 dual_link;

		dual_link = dual_link_from_link(link);
		अगर (dual_link)
			sw = tb_चयन_find_by_link_depth(tb, dual_link, depth);
	पूर्ण
	अगर (sw) अणु
		हटाओ_चयन(sw);
		tb_चयन_put(sw);
	पूर्ण

	/* Remove existing XDoमुख्य connection अगर found */
	xd = tb_xकरोमुख्य_find_by_link_depth(tb, link, depth);
	अगर (xd) अणु
		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण

	parent_sw = tb_चयन_find_by_link_depth(tb, link, depth - 1);
	अगर (!parent_sw) अणु
		tb_err(tb, "failed to find parent switch for %u.%u\n",
		       link, depth);
		वापस;
	पूर्ण

	ret = icm->get_route(tb, link, depth, &route);
	अगर (ret) अणु
		tb_err(tb, "failed to find route string for switch at %u.%u\n",
		       link, depth);
		tb_चयन_put(parent_sw);
		वापस;
	पूर्ण

	pm_runसमय_get_sync(&parent_sw->dev);

	sw = alloc_चयन(parent_sw, route, &pkg->ep_uuid);
	अगर (!IS_ERR(sw)) अणु
		sw->connection_id = pkg->connection_id;
		sw->connection_key = pkg->connection_key;
		sw->link = link;
		sw->depth = depth;
		sw->authorized = authorized;
		sw->security_level = security_level;
		sw->boot = boot;
		sw->link_speed = speed_gen3 ? 20 : 10;
		sw->link_width = dual_lane ? 2 : 1;
		sw->rpm = पूर्णांकel_vss_is_rtd3(pkg->ep_name, माप(pkg->ep_name));

		अगर (add_चयन(parent_sw, sw))
			tb_चयन_put(sw);
	पूर्ण

	pm_runसमय_mark_last_busy(&parent_sw->dev);
	pm_runसमय_put_स्वतःsuspend(&parent_sw->dev);

	tb_चयन_put(parent_sw);
पूर्ण

अटल व्योम
icm_fr_device_disconnected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_fr_event_device_disconnected *pkg =
		(स्थिर काष्ठा icm_fr_event_device_disconnected *)hdr;
	काष्ठा tb_चयन *sw;
	u8 link, depth;

	link = pkg->link_info & ICM_LINK_INFO_LINK_MASK;
	depth = (pkg->link_info & ICM_LINK_INFO_DEPTH_MASK) >>
		ICM_LINK_INFO_DEPTH_SHIFT;

	अगर (link > ICM_MAX_LINK || depth > TB_SWITCH_MAX_DEPTH) अणु
		tb_warn(tb, "invalid topology %u.%u, ignoring\n", link, depth);
		वापस;
	पूर्ण

	sw = tb_चयन_find_by_link_depth(tb, link, depth);
	अगर (!sw) अणु
		tb_warn(tb, "no switch exists at %u.%u, ignoring\n", link,
			depth);
		वापस;
	पूर्ण

	pm_runसमय_get_sync(sw->dev.parent);

	हटाओ_चयन(sw);

	pm_runसमय_mark_last_busy(sw->dev.parent);
	pm_runसमय_put_स्वतःsuspend(sw->dev.parent);

	tb_चयन_put(sw);
पूर्ण

अटल व्योम
icm_fr_xकरोमुख्य_connected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_fr_event_xकरोमुख्य_connected *pkg =
		(स्थिर काष्ठा icm_fr_event_xकरोमुख्य_connected *)hdr;
	काष्ठा tb_xकरोमुख्य *xd;
	काष्ठा tb_चयन *sw;
	u8 link, depth;
	u64 route;

	link = pkg->link_info & ICM_LINK_INFO_LINK_MASK;
	depth = (pkg->link_info & ICM_LINK_INFO_DEPTH_MASK) >>
		ICM_LINK_INFO_DEPTH_SHIFT;

	अगर (link > ICM_MAX_LINK || depth > TB_SWITCH_MAX_DEPTH) अणु
		tb_warn(tb, "invalid topology %u.%u, ignoring\n", link, depth);
		वापस;
	पूर्ण

	route = get_route(pkg->local_route_hi, pkg->local_route_lo);

	xd = tb_xकरोमुख्य_find_by_uuid(tb, &pkg->remote_uuid);
	अगर (xd) अणु
		u8 xd_phy_port, phy_port;

		xd_phy_port = phy_port_from_route(xd->route, xd->depth);
		phy_port = phy_port_from_route(route, depth);

		अगर (xd->depth == depth && xd_phy_port == phy_port) अणु
			update_xकरोमुख्य(xd, route, link);
			tb_xकरोमुख्य_put(xd);
			वापस;
		पूर्ण

		/*
		 * If we find an existing XDoमुख्य connection हटाओ it
		 * now. We need to go through login handshake and
		 * everything anyway to be able to re-establish the
		 * connection.
		 */
		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण

	/*
	 * Look अगर there alपढ़ोy exists an XDoमुख्य in the same place
	 * than the new one and in that हाल हटाओ it because it is
	 * most likely another host that got disconnected.
	 */
	xd = tb_xकरोमुख्य_find_by_link_depth(tb, link, depth);
	अगर (!xd) अणु
		u8 dual_link;

		dual_link = dual_link_from_link(link);
		अगर (dual_link)
			xd = tb_xकरोमुख्य_find_by_link_depth(tb, dual_link,
							   depth);
	पूर्ण
	अगर (xd) अणु
		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण

	/*
	 * If the user disconnected a चयन during suspend and
	 * connected another host to the same port, हटाओ the चयन
	 * first.
	 */
	sw = tb_चयन_find_by_route(tb, route);
	अगर (sw) अणु
		हटाओ_चयन(sw);
		tb_चयन_put(sw);
	पूर्ण

	sw = tb_चयन_find_by_link_depth(tb, link, depth);
	अगर (!sw) अणु
		tb_warn(tb, "no switch exists at %u.%u, ignoring\n", link,
			depth);
		वापस;
	पूर्ण

	add_xकरोमुख्य(sw, route, &pkg->local_uuid, &pkg->remote_uuid, link,
		    depth);
	tb_चयन_put(sw);
पूर्ण

अटल व्योम
icm_fr_xकरोमुख्य_disconnected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_fr_event_xकरोमुख्य_disconnected *pkg =
		(स्थिर काष्ठा icm_fr_event_xकरोमुख्य_disconnected *)hdr;
	काष्ठा tb_xकरोमुख्य *xd;

	/*
	 * If the connection is through one or multiple devices, the
	 * XDoमुख्य device is हटाओd aदीर्घ with them so it is fine अगर we
	 * cannot find it here.
	 */
	xd = tb_xकरोमुख्य_find_by_uuid(tb, &pkg->remote_uuid);
	अगर (xd) अणु
		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण
पूर्ण

अटल पूर्णांक icm_tr_cio_reset(काष्ठा tb *tb)
अणु
	वापस pcie2cio_ग_लिखो(tb_priv(tb), TB_CFG_SWITCH, 0, 0x777, BIT(1));
पूर्ण

अटल पूर्णांक
icm_tr_driver_पढ़ोy(काष्ठा tb *tb, क्रमागत tb_security_level *security_level,
		    u8 *proto_version, माप_प्रकार *nboot_acl, bool *rpm)
अणु
	काष्ठा icm_tr_pkg_driver_पढ़ोy_response reply;
	काष्ठा icm_pkg_driver_पढ़ोy request = अणु
		.hdr.code = ICM_DRIVER_READY,
	पूर्ण;
	पूर्णांक ret;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, 20000);
	अगर (ret)
		वापस ret;

	अगर (security_level)
		*security_level = reply.info & ICM_TR_INFO_SLEVEL_MASK;
	अगर (proto_version)
		*proto_version = (reply.info & ICM_TR_INFO_PROTO_VERSION_MASK) >>
				ICM_TR_INFO_PROTO_VERSION_SHIFT;
	अगर (nboot_acl)
		*nboot_acl = (reply.info & ICM_TR_INFO_BOOT_ACL_MASK) >>
				ICM_TR_INFO_BOOT_ACL_SHIFT;
	अगर (rpm)
		*rpm = !!(reply.hdr.flags & ICM_TR_FLAGS_RTD3);

	वापस 0;
पूर्ण

अटल पूर्णांक icm_tr_approve_चयन(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा icm_tr_pkg_approve_device request;
	काष्ठा icm_tr_pkg_approve_device reply;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	स_नकल(&request.ep_uuid, sw->uuid, माप(request.ep_uuid));
	request.hdr.code = ICM_APPROVE_DEVICE;
	request.route_lo = sw->config.route_lo;
	request.route_hi = sw->config.route_hi;
	request.connection_id = sw->connection_id;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_APPROVE_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR) अणु
		tb_warn(tb, "PCIe tunnel creation failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icm_tr_add_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा icm_tr_pkg_add_device_key_response reply;
	काष्ठा icm_tr_pkg_add_device_key request;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	स_नकल(&request.ep_uuid, sw->uuid, माप(request.ep_uuid));
	request.hdr.code = ICM_ADD_DEVICE_KEY;
	request.route_lo = sw->config.route_lo;
	request.route_hi = sw->config.route_hi;
	request.connection_id = sw->connection_id;
	स_नकल(request.key, sw->key, TB_SWITCH_KEY_SIZE);

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR) अणु
		tb_warn(tb, "Adding key to switch failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icm_tr_challenge_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw,
				       स्थिर u8 *challenge, u8 *response)
अणु
	काष्ठा icm_tr_pkg_challenge_device_response reply;
	काष्ठा icm_tr_pkg_challenge_device request;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	स_नकल(&request.ep_uuid, sw->uuid, माप(request.ep_uuid));
	request.hdr.code = ICM_CHALLENGE_DEVICE;
	request.route_lo = sw->config.route_lo;
	request.route_hi = sw->config.route_hi;
	request.connection_id = sw->connection_id;
	स_नकल(request.challenge, challenge, TB_SWITCH_KEY_SIZE);

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EKEYREJECTED;
	अगर (reply.hdr.flags & ICM_FLAGS_NO_KEY)
		वापस -ENOKEY;

	स_नकल(response, reply.response, TB_SWITCH_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक icm_tr_approve_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
					पूर्णांक transmit_path, पूर्णांक transmit_ring,
					पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	काष्ठा icm_tr_pkg_approve_xकरोमुख्य_response reply;
	काष्ठा icm_tr_pkg_approve_xकरोमुख्य request;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	request.hdr.code = ICM_APPROVE_XDOMAIN;
	request.route_hi = upper_32_bits(xd->route);
	request.route_lo = lower_32_bits(xd->route);
	request.transmit_path = transmit_path;
	request.transmit_ring = transmit_ring;
	request.receive_path = receive_path;
	request.receive_ring = receive_ring;
	स_नकल(&request.remote_uuid, xd->remote_uuid, माप(*xd->remote_uuid));

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक icm_tr_xकरोमुख्य_tear_करोwn(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				    पूर्णांक stage)
अणु
	काष्ठा icm_tr_pkg_disconnect_xकरोमुख्य_response reply;
	काष्ठा icm_tr_pkg_disconnect_xकरोमुख्य request;
	पूर्णांक ret;

	स_रखो(&request, 0, माप(request));
	request.hdr.code = ICM_DISCONNECT_XDOMAIN;
	request.stage = stage;
	request.route_hi = upper_32_bits(xd->route);
	request.route_lo = lower_32_bits(xd->route);
	स_नकल(&request.remote_uuid, xd->remote_uuid, माप(*xd->remote_uuid));

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक icm_tr_disconnect_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
					   पूर्णांक transmit_path, पूर्णांक transmit_ring,
					   पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	पूर्णांक ret;

	ret = icm_tr_xकरोमुख्य_tear_करोwn(tb, xd, 1);
	अगर (ret)
		वापस ret;

	usleep_range(10, 50);
	वापस icm_tr_xकरोमुख्य_tear_करोwn(tb, xd, 2);
पूर्ण

अटल व्योम
__icm_tr_device_connected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr,
			  bool क्रमce_rtd3)
अणु
	स्थिर काष्ठा icm_tr_event_device_connected *pkg =
		(स्थिर काष्ठा icm_tr_event_device_connected *)hdr;
	bool authorized, boot, dual_lane, speed_gen3;
	क्रमागत tb_security_level security_level;
	काष्ठा tb_चयन *sw, *parent_sw;
	काष्ठा tb_xकरोमुख्य *xd;
	u64 route;

	icm_postpone_rescan(tb);

	/*
	 * Currently we करोn't use the QoS inक्रमmation coming with the
	 * device connected message so simply just ignore that extra
	 * packet क्रम now.
	 */
	अगर (pkg->hdr.packet_id)
		वापस;

	route = get_route(pkg->route_hi, pkg->route_lo);
	authorized = pkg->link_info & ICM_LINK_INFO_APPROVED;
	security_level = (pkg->hdr.flags & ICM_FLAGS_SLEVEL_MASK) >>
			 ICM_FLAGS_SLEVEL_SHIFT;
	boot = pkg->link_info & ICM_LINK_INFO_BOOT;
	dual_lane = pkg->hdr.flags & ICM_FLAGS_DUAL_LANE;
	speed_gen3 = pkg->hdr.flags & ICM_FLAGS_SPEED_GEN3;

	अगर (pkg->link_info & ICM_LINK_INFO_REJECTED) अणु
		tb_info(tb, "switch at %llx was rejected by ICM firmware because topology limit exceeded\n",
			route);
		वापस;
	पूर्ण

	sw = tb_चयन_find_by_uuid(tb, &pkg->ep_uuid);
	अगर (sw) अणु
		/* Update the चयन अगर it is still in the same place */
		अगर (tb_route(sw) == route && !!sw->authorized == authorized) अणु
			parent_sw = tb_to_चयन(sw->dev.parent);
			update_चयन(parent_sw, sw, route, pkg->connection_id,
				      0, 0, 0, boot);
			tb_चयन_put(sw);
			वापस;
		पूर्ण

		हटाओ_चयन(sw);
		tb_चयन_put(sw);
	पूर्ण

	/* Another चयन with the same address */
	sw = tb_चयन_find_by_route(tb, route);
	अगर (sw) अणु
		हटाओ_चयन(sw);
		tb_चयन_put(sw);
	पूर्ण

	/* XDoमुख्य connection with the same address */
	xd = tb_xकरोमुख्य_find_by_route(tb, route);
	अगर (xd) अणु
		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण

	parent_sw = tb_चयन_find_by_route(tb, get_parent_route(route));
	अगर (!parent_sw) अणु
		tb_err(tb, "failed to find parent switch for %llx\n", route);
		वापस;
	पूर्ण

	pm_runसमय_get_sync(&parent_sw->dev);

	sw = alloc_चयन(parent_sw, route, &pkg->ep_uuid);
	अगर (!IS_ERR(sw)) अणु
		sw->connection_id = pkg->connection_id;
		sw->authorized = authorized;
		sw->security_level = security_level;
		sw->boot = boot;
		sw->link_speed = speed_gen3 ? 20 : 10;
		sw->link_width = dual_lane ? 2 : 1;
		sw->rpm = क्रमce_rtd3;
		अगर (!sw->rpm)
			sw->rpm = पूर्णांकel_vss_is_rtd3(pkg->ep_name,
						    माप(pkg->ep_name));

		अगर (add_चयन(parent_sw, sw))
			tb_चयन_put(sw);
	पूर्ण

	pm_runसमय_mark_last_busy(&parent_sw->dev);
	pm_runसमय_put_स्वतःsuspend(&parent_sw->dev);

	tb_चयन_put(parent_sw);
पूर्ण

अटल व्योम
icm_tr_device_connected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	__icm_tr_device_connected(tb, hdr, false);
पूर्ण

अटल व्योम
icm_tr_device_disconnected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_tr_event_device_disconnected *pkg =
		(स्थिर काष्ठा icm_tr_event_device_disconnected *)hdr;
	काष्ठा tb_चयन *sw;
	u64 route;

	route = get_route(pkg->route_hi, pkg->route_lo);

	sw = tb_चयन_find_by_route(tb, route);
	अगर (!sw) अणु
		tb_warn(tb, "no switch exists at %llx, ignoring\n", route);
		वापस;
	पूर्ण
	pm_runसमय_get_sync(sw->dev.parent);

	हटाओ_चयन(sw);

	pm_runसमय_mark_last_busy(sw->dev.parent);
	pm_runसमय_put_स्वतःsuspend(sw->dev.parent);

	tb_चयन_put(sw);
पूर्ण

अटल व्योम
icm_tr_xकरोमुख्य_connected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_tr_event_xकरोमुख्य_connected *pkg =
		(स्थिर काष्ठा icm_tr_event_xकरोमुख्य_connected *)hdr;
	काष्ठा tb_xकरोमुख्य *xd;
	काष्ठा tb_चयन *sw;
	u64 route;

	अगर (!tb->root_चयन)
		वापस;

	route = get_route(pkg->local_route_hi, pkg->local_route_lo);

	xd = tb_xकरोमुख्य_find_by_uuid(tb, &pkg->remote_uuid);
	अगर (xd) अणु
		अगर (xd->route == route) अणु
			update_xकरोमुख्य(xd, route, 0);
			tb_xकरोमुख्य_put(xd);
			वापस;
		पूर्ण

		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण

	/* An existing xकरोमुख्य with the same address */
	xd = tb_xकरोमुख्य_find_by_route(tb, route);
	अगर (xd) अणु
		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण

	/*
	 * If the user disconnected a चयन during suspend and
	 * connected another host to the same port, हटाओ the चयन
	 * first.
	 */
	sw = tb_चयन_find_by_route(tb, route);
	अगर (sw) अणु
		हटाओ_चयन(sw);
		tb_चयन_put(sw);
	पूर्ण

	sw = tb_चयन_find_by_route(tb, get_parent_route(route));
	अगर (!sw) अणु
		tb_warn(tb, "no switch exists at %llx, ignoring\n", route);
		वापस;
	पूर्ण

	add_xकरोमुख्य(sw, route, &pkg->local_uuid, &pkg->remote_uuid, 0, 0);
	tb_चयन_put(sw);
पूर्ण

अटल व्योम
icm_tr_xकरोमुख्य_disconnected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_tr_event_xकरोमुख्य_disconnected *pkg =
		(स्थिर काष्ठा icm_tr_event_xकरोमुख्य_disconnected *)hdr;
	काष्ठा tb_xकरोमुख्य *xd;
	u64 route;

	route = get_route(pkg->route_hi, pkg->route_lo);

	xd = tb_xकरोमुख्य_find_by_route(tb, route);
	अगर (xd) अणु
		हटाओ_xकरोमुख्य(xd);
		tb_xकरोमुख्य_put(xd);
	पूर्ण
पूर्ण

अटल काष्ठा pci_dev *get_upstream_port(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *parent;

	parent = pci_upstream_bridge(pdev);
	जबतक (parent) अणु
		अगर (!pci_is_pcie(parent))
			वापस शून्य;
		अगर (pci_pcie_type(parent) == PCI_EXP_TYPE_UPSTREAM)
			अवरोध;
		parent = pci_upstream_bridge(parent);
	पूर्ण

	अगर (!parent)
		वापस शून्य;

	चयन (parent->device) अणु
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE:
	हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE:
		वापस parent;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool icm_ar_is_supported(काष्ठा tb *tb)
अणु
	काष्ठा pci_dev *upstream_port;
	काष्ठा icm *icm = tb_priv(tb);

	/*
	 * Starting from Alpine Ridge we can use ICM on Apple machines
	 * as well. We just need to reset and re-enable it first.
	 * However, only start it अगर explicitly asked by the user.
	 */
	अगर (icm_firmware_running(tb->nhi))
		वापस true;
	अगर (!start_icm)
		वापस false;

	/*
	 * Find the upstream PCIe port in हाल we need to करो reset
	 * through its venकरोr specअगरic रेजिस्टरs.
	 */
	upstream_port = get_upstream_port(tb->nhi->pdev);
	अगर (upstream_port) अणु
		पूर्णांक cap;

		cap = pci_find_ext_capability(upstream_port,
					      PCI_EXT_CAP_ID_VNDR);
		अगर (cap > 0) अणु
			icm->upstream_port = upstream_port;
			icm->vnd_cap = cap;

			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक icm_ar_cio_reset(काष्ठा tb *tb)
अणु
	वापस pcie2cio_ग_लिखो(tb_priv(tb), TB_CFG_SWITCH, 0, 0x50, BIT(9));
पूर्ण

अटल पूर्णांक icm_ar_get_mode(काष्ठा tb *tb)
अणु
	काष्ठा tb_nhi *nhi = tb->nhi;
	पूर्णांक retries = 60;
	u32 val;

	करो अणु
		val = ioपढ़ो32(nhi->iobase + REG_FW_STS);
		अगर (val & REG_FW_STS_NVM_AUTH_DONE)
			अवरोध;
		msleep(50);
	पूर्ण जबतक (--retries);

	अगर (!retries) अणु
		dev_err(&nhi->pdev->dev, "ICM firmware not authenticated\n");
		वापस -ENODEV;
	पूर्ण

	वापस nhi_mailbox_mode(nhi);
पूर्ण

अटल पूर्णांक
icm_ar_driver_पढ़ोy(काष्ठा tb *tb, क्रमागत tb_security_level *security_level,
		    u8 *proto_version, माप_प्रकार *nboot_acl, bool *rpm)
अणु
	काष्ठा icm_ar_pkg_driver_पढ़ोy_response reply;
	काष्ठा icm_pkg_driver_पढ़ोy request = अणु
		.hdr.code = ICM_DRIVER_READY,
	पूर्ण;
	पूर्णांक ret;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (security_level)
		*security_level = reply.info & ICM_AR_INFO_SLEVEL_MASK;
	अगर (nboot_acl && (reply.info & ICM_AR_INFO_BOOT_ACL_SUPPORTED))
		*nboot_acl = (reply.info & ICM_AR_INFO_BOOT_ACL_MASK) >>
				ICM_AR_INFO_BOOT_ACL_SHIFT;
	अगर (rpm)
		*rpm = !!(reply.hdr.flags & ICM_AR_FLAGS_RTD3);

	वापस 0;
पूर्ण

अटल पूर्णांक icm_ar_get_route(काष्ठा tb *tb, u8 link, u8 depth, u64 *route)
अणु
	काष्ठा icm_ar_pkg_get_route_response reply;
	काष्ठा icm_ar_pkg_get_route request = अणु
		.hdr = अणु .code = ICM_GET_ROUTE पूर्ण,
		.link_info = depth << ICM_LINK_INFO_DEPTH_SHIFT | link,
	पूर्ण;
	पूर्णांक ret;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EIO;

	*route = get_route(reply.route_hi, reply.route_lo);
	वापस 0;
पूर्ण

अटल पूर्णांक icm_ar_get_boot_acl(काष्ठा tb *tb, uuid_t *uuids, माप_प्रकार nuuids)
अणु
	काष्ठा icm_ar_pkg_preboot_acl_response reply;
	काष्ठा icm_ar_pkg_preboot_acl request = अणु
		.hdr = अणु .code = ICM_PREBOOT_ACL पूर्ण,
	पूर्ण;
	पूर्णांक ret, i;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EIO;

	क्रम (i = 0; i < nuuids; i++) अणु
		u32 *uuid = (u32 *)&uuids[i];

		uuid[0] = reply.acl[i].uuid_lo;
		uuid[1] = reply.acl[i].uuid_hi;

		अगर (uuid[0] == 0xffffffff && uuid[1] == 0xffffffff) अणु
			/* Map empty entries to null UUID */
			uuid[0] = 0;
			uuid[1] = 0;
		पूर्ण अन्यथा अगर (uuid[0] != 0 || uuid[1] != 0) अणु
			/* Upper two DWs are always one's */
			uuid[2] = 0xffffffff;
			uuid[3] = 0xffffffff;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक icm_ar_set_boot_acl(काष्ठा tb *tb, स्थिर uuid_t *uuids,
			       माप_प्रकार nuuids)
अणु
	काष्ठा icm_ar_pkg_preboot_acl_response reply;
	काष्ठा icm_ar_pkg_preboot_acl request = अणु
		.hdr = अणु
			.code = ICM_PREBOOT_ACL,
			.flags = ICM_FLAGS_WRITE,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret, i;

	क्रम (i = 0; i < nuuids; i++) अणु
		स्थिर u32 *uuid = (स्थिर u32 *)&uuids[i];

		अगर (uuid_is_null(&uuids[i])) अणु
			/*
			 * Map null UUID to the empty (all one) entries
			 * क्रम ICM.
			 */
			request.acl[i].uuid_lo = 0xffffffff;
			request.acl[i].uuid_hi = 0xffffffff;
		पूर्ण अन्यथा अणु
			/* Two high DWs need to be set to all one */
			अगर (uuid[2] != 0xffffffff || uuid[3] != 0xffffffff)
				वापस -EINVAL;

			request.acl[i].uuid_lo = uuid[0];
			request.acl[i].uuid_hi = uuid[1];
		पूर्ण
	पूर्ण

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
icm_icl_driver_पढ़ोy(काष्ठा tb *tb, क्रमागत tb_security_level *security_level,
		     u8 *proto_version, माप_प्रकार *nboot_acl, bool *rpm)
अणु
	काष्ठा icm_tr_pkg_driver_पढ़ोy_response reply;
	काष्ठा icm_pkg_driver_पढ़ोy request = अणु
		.hdr.code = ICM_DRIVER_READY,
	पूर्ण;
	पूर्णांक ret;

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, 20000);
	अगर (ret)
		वापस ret;

	अगर (proto_version)
		*proto_version = (reply.info & ICM_TR_INFO_PROTO_VERSION_MASK) >>
				ICM_TR_INFO_PROTO_VERSION_SHIFT;

	/* Ice Lake always supports RTD3 */
	अगर (rpm)
		*rpm = true;

	वापस 0;
पूर्ण

अटल व्योम icm_icl_set_uuid(काष्ठा tb *tb)
अणु
	काष्ठा tb_nhi *nhi = tb->nhi;
	u32 uuid[4];

	pci_पढ़ो_config_dword(nhi->pdev, VS_CAP_10, &uuid[0]);
	pci_पढ़ो_config_dword(nhi->pdev, VS_CAP_11, &uuid[1]);
	uuid[2] = 0xffffffff;
	uuid[3] = 0xffffffff;

	tb->root_चयन->uuid = kmemdup(uuid, माप(uuid), GFP_KERNEL);
पूर्ण

अटल व्योम
icm_icl_device_connected(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	__icm_tr_device_connected(tb, hdr, true);
पूर्ण

अटल व्योम icm_icl_rtd3_veto(काष्ठा tb *tb, स्थिर काष्ठा icm_pkg_header *hdr)
अणु
	स्थिर काष्ठा icm_icl_event_rtd3_veto *pkg =
		(स्थिर काष्ठा icm_icl_event_rtd3_veto *)hdr;

	tb_dbg(tb, "ICM rtd3 veto=0x%08x\n", pkg->veto_reason);

	अगर (pkg->veto_reason)
		icm_veto_begin(tb);
	अन्यथा
		icm_veto_end(tb);
पूर्ण

अटल bool icm_tgl_is_supported(काष्ठा tb *tb)
अणु
	u32 val;

	/*
	 * If the firmware is not running use software CM. This platक्रमm
	 * should fully support both.
	 */
	val = ioपढ़ो32(tb->nhi->iobase + REG_FW_STS);
	वापस !!(val & REG_FW_STS_NVM_AUTH_DONE);
पूर्ण

अटल व्योम icm_handle_notअगरication(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा icm_notअगरication *n = container_of(work, typeof(*n), work);
	काष्ठा tb *tb = n->tb;
	काष्ठा icm *icm = tb_priv(tb);

	mutex_lock(&tb->lock);

	/*
	 * When the करोमुख्य is stopped we flush its workqueue but beक्रमe
	 * that the root चयन is हटाओd. In that हाल we should treat
	 * the queued events as being canceled.
	 */
	अगर (tb->root_चयन) अणु
		चयन (n->pkg->code) अणु
		हाल ICM_EVENT_DEVICE_CONNECTED:
			icm->device_connected(tb, n->pkg);
			अवरोध;
		हाल ICM_EVENT_DEVICE_DISCONNECTED:
			icm->device_disconnected(tb, n->pkg);
			अवरोध;
		हाल ICM_EVENT_XDOMAIN_CONNECTED:
			अगर (tb_is_xकरोमुख्य_enabled())
				icm->xकरोमुख्य_connected(tb, n->pkg);
			अवरोध;
		हाल ICM_EVENT_XDOMAIN_DISCONNECTED:
			अगर (tb_is_xकरोमुख्य_enabled())
				icm->xकरोमुख्य_disconnected(tb, n->pkg);
			अवरोध;
		हाल ICM_EVENT_RTD3_VETO:
			icm->rtd3_veto(tb, n->pkg);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&tb->lock);

	kमुक्त(n->pkg);
	kमुक्त(n);
पूर्ण

अटल व्योम icm_handle_event(काष्ठा tb *tb, क्रमागत tb_cfg_pkg_type type,
			     स्थिर व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा icm_notअगरication *n;

	n = kदो_स्मृति(माप(*n), GFP_KERNEL);
	अगर (!n)
		वापस;

	INIT_WORK(&n->work, icm_handle_notअगरication);
	n->pkg = kmemdup(buf, size, GFP_KERNEL);
	n->tb = tb;

	queue_work(tb->wq, &n->work);
पूर्ण

अटल पूर्णांक
__icm_driver_पढ़ोy(काष्ठा tb *tb, क्रमागत tb_security_level *security_level,
		   u8 *proto_version, माप_प्रकार *nboot_acl, bool *rpm)
अणु
	काष्ठा icm *icm = tb_priv(tb);
	अचिन्हित पूर्णांक retries = 50;
	पूर्णांक ret;

	ret = icm->driver_पढ़ोy(tb, security_level, proto_version, nboot_acl,
				rpm);
	अगर (ret) अणु
		tb_err(tb, "failed to send driver ready to ICM\n");
		वापस ret;
	पूर्ण

	/*
	 * Hold on here until the चयन config space is accessible so
	 * that we can पढ़ो root चयन config successfully.
	 */
	करो अणु
		काष्ठा tb_cfg_result res;
		u32 पंचांगp;

		res = tb_cfg_पढ़ो_raw(tb->ctl, &पंचांगp, 0, 0, TB_CFG_SWITCH,
				      0, 1, 100);
		अगर (!res.err)
			वापस 0;

		msleep(50);
	पूर्ण जबतक (--retries);

	tb_err(tb, "failed to read root switch config space, giving up\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक icm_firmware_reset(काष्ठा tb *tb, काष्ठा tb_nhi *nhi)
अणु
	काष्ठा icm *icm = tb_priv(tb);
	u32 val;

	अगर (!icm->upstream_port)
		वापस -ENODEV;

	/* Put ARC to रुको क्रम CIO reset event to happen */
	val = ioपढ़ो32(nhi->iobase + REG_FW_STS);
	val |= REG_FW_STS_CIO_RESET_REQ;
	ioग_लिखो32(val, nhi->iobase + REG_FW_STS);

	/* Re-start ARC */
	val = ioपढ़ो32(nhi->iobase + REG_FW_STS);
	val |= REG_FW_STS_ICM_EN_INVERT;
	val |= REG_FW_STS_ICM_EN_CPU;
	ioग_लिखो32(val, nhi->iobase + REG_FW_STS);

	/* Trigger CIO reset now */
	वापस icm->cio_reset(tb);
पूर्ण

अटल पूर्णांक icm_firmware_start(काष्ठा tb *tb, काष्ठा tb_nhi *nhi)
अणु
	अचिन्हित पूर्णांक retries = 10;
	पूर्णांक ret;
	u32 val;

	/* Check अगर the ICM firmware is alपढ़ोy running */
	अगर (icm_firmware_running(nhi))
		वापस 0;

	dev_dbg(&nhi->pdev->dev, "starting ICM firmware\n");

	ret = icm_firmware_reset(tb, nhi);
	अगर (ret)
		वापस ret;

	/* Wait until the ICM firmware tells us it is up and running */
	करो अणु
		/* Check that the ICM firmware is running */
		val = ioपढ़ो32(nhi->iobase + REG_FW_STS);
		अगर (val & REG_FW_STS_NVM_AUTH_DONE)
			वापस 0;

		msleep(300);
	पूर्ण जबतक (--retries);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक icm_reset_phy_port(काष्ठा tb *tb, पूर्णांक phy_port)
अणु
	काष्ठा icm *icm = tb_priv(tb);
	u32 state0, state1;
	पूर्णांक port0, port1;
	u32 val0, val1;
	पूर्णांक ret;

	अगर (!icm->upstream_port)
		वापस 0;

	अगर (phy_port) अणु
		port0 = 3;
		port1 = 4;
	पूर्ण अन्यथा अणु
		port0 = 1;
		port1 = 2;
	पूर्ण

	/*
	 * Read link status of both null ports beदीर्घing to a single
	 * physical port.
	 */
	ret = pcie2cio_पढ़ो(icm, TB_CFG_PORT, port0, PHY_PORT_CS1, &val0);
	अगर (ret)
		वापस ret;
	ret = pcie2cio_पढ़ो(icm, TB_CFG_PORT, port1, PHY_PORT_CS1, &val1);
	अगर (ret)
		वापस ret;

	state0 = val0 & PHY_PORT_CS1_LINK_STATE_MASK;
	state0 >>= PHY_PORT_CS1_LINK_STATE_SHIFT;
	state1 = val1 & PHY_PORT_CS1_LINK_STATE_MASK;
	state1 >>= PHY_PORT_CS1_LINK_STATE_SHIFT;

	/* If they are both up we need to reset them now */
	अगर (state0 != TB_PORT_UP || state1 != TB_PORT_UP)
		वापस 0;

	val0 |= PHY_PORT_CS1_LINK_DISABLE;
	ret = pcie2cio_ग_लिखो(icm, TB_CFG_PORT, port0, PHY_PORT_CS1, val0);
	अगर (ret)
		वापस ret;

	val1 |= PHY_PORT_CS1_LINK_DISABLE;
	ret = pcie2cio_ग_लिखो(icm, TB_CFG_PORT, port1, PHY_PORT_CS1, val1);
	अगर (ret)
		वापस ret;

	/* Wait a bit and then re-enable both ports */
	usleep_range(10, 100);

	ret = pcie2cio_पढ़ो(icm, TB_CFG_PORT, port0, PHY_PORT_CS1, &val0);
	अगर (ret)
		वापस ret;
	ret = pcie2cio_पढ़ो(icm, TB_CFG_PORT, port1, PHY_PORT_CS1, &val1);
	अगर (ret)
		वापस ret;

	val0 &= ~PHY_PORT_CS1_LINK_DISABLE;
	ret = pcie2cio_ग_लिखो(icm, TB_CFG_PORT, port0, PHY_PORT_CS1, val0);
	अगर (ret)
		वापस ret;

	val1 &= ~PHY_PORT_CS1_LINK_DISABLE;
	वापस pcie2cio_ग_लिखो(icm, TB_CFG_PORT, port1, PHY_PORT_CS1, val1);
पूर्ण

अटल पूर्णांक icm_firmware_init(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);
	काष्ठा tb_nhi *nhi = tb->nhi;
	पूर्णांक ret;

	ret = icm_firmware_start(tb, nhi);
	अगर (ret) अणु
		dev_err(&nhi->pdev->dev, "could not start ICM firmware\n");
		वापस ret;
	पूर्ण

	अगर (icm->get_mode) अणु
		ret = icm->get_mode(tb);

		चयन (ret) अणु
		हाल NHI_FW_SAFE_MODE:
			icm->safe_mode = true;
			अवरोध;

		हाल NHI_FW_CM_MODE:
			/* Ask ICM to accept all Thunderbolt devices */
			nhi_mailbox_cmd(nhi, NHI_MAILBOX_ALLOW_ALL_DEVS, 0);
			अवरोध;

		शेष:
			अगर (ret < 0)
				वापस ret;

			tb_err(tb, "ICM firmware is in wrong mode: %u\n", ret);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * Reset both physical ports अगर there is anything connected to
	 * them alपढ़ोy.
	 */
	ret = icm_reset_phy_port(tb, 0);
	अगर (ret)
		dev_warn(&nhi->pdev->dev, "failed to reset links on port0\n");
	ret = icm_reset_phy_port(tb, 1);
	अगर (ret)
		dev_warn(&nhi->pdev->dev, "failed to reset links on port1\n");

	वापस 0;
पूर्ण

अटल पूर्णांक icm_driver_पढ़ोy(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);
	पूर्णांक ret;

	ret = icm_firmware_init(tb);
	अगर (ret)
		वापस ret;

	अगर (icm->safe_mode) अणु
		tb_info(tb, "Thunderbolt host controller is in safe mode.\n");
		tb_info(tb, "You need to update NVM firmware of the controller before it can be used.\n");
		tb_info(tb, "For latest updates check https://thunderbolttechnology.net/updates.\n");
		वापस 0;
	पूर्ण

	ret = __icm_driver_पढ़ोy(tb, &tb->security_level, &icm->proto_version,
				 &tb->nboot_acl, &icm->rpm);
	अगर (ret)
		वापस ret;

	/*
	 * Make sure the number of supported preboot ACL matches what we
	 * expect or disable the whole feature.
	 */
	अगर (tb->nboot_acl > icm->max_boot_acl)
		tb->nboot_acl = 0;

	अगर (icm->proto_version >= 3)
		tb_dbg(tb, "USB4 proxy operations supported\n");

	वापस 0;
पूर्ण

अटल पूर्णांक icm_suspend(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);

	अगर (icm->save_devices)
		icm->save_devices(tb);

	nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_DRV_UNLOADS, 0);
	वापस 0;
पूर्ण

/*
 * Mark all चयनes (except root चयन) below this one unplugged. ICM
 * firmware will send us an updated list of चयनes after we have send
 * it driver पढ़ोy command. If a चयन is not in that list it will be
 * हटाओd when we perक्रमm rescan.
 */
अटल व्योम icm_unplug_children(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;

	अगर (tb_route(sw))
		sw->is_unplugged = true;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (port->xकरोमुख्य)
			port->xकरोमुख्य->is_unplugged = true;
		अन्यथा अगर (tb_port_has_remote(port))
			icm_unplug_children(port->remote->sw);
	पूर्ण
पूर्ण

अटल पूर्णांक complete_rpm(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा tb_चयन *sw = tb_to_चयन(dev);

	अगर (sw)
		complete(&sw->rpm_complete);
	वापस 0;
पूर्ण

अटल व्योम हटाओ_unplugged_चयन(काष्ठा tb_चयन *sw)
अणु
	काष्ठा device *parent = get_device(sw->dev.parent);

	pm_runसमय_get_sync(parent);

	/*
	 * Signal this and चयनes below क्रम rpm_complete because
	 * tb_चयन_हटाओ() calls pm_runसमय_get_sync() that then रुकोs
	 * क्रम it.
	 */
	complete_rpm(&sw->dev, शून्य);
	bus_क्रम_each_dev(&tb_bus_type, &sw->dev, शून्य, complete_rpm);
	tb_चयन_हटाओ(sw);

	pm_runसमय_mark_last_busy(parent);
	pm_runसमय_put_स्वतःsuspend(parent);

	put_device(parent);
पूर्ण

अटल व्योम icm_मुक्त_unplugged_children(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (port->xकरोमुख्य && port->xकरोमुख्य->is_unplugged) अणु
			tb_xकरोमुख्य_हटाओ(port->xकरोमुख्य);
			port->xकरोमुख्य = शून्य;
		पूर्ण अन्यथा अगर (tb_port_has_remote(port)) अणु
			अगर (port->remote->sw->is_unplugged) अणु
				हटाओ_unplugged_चयन(port->remote->sw);
				port->remote = शून्य;
			पूर्ण अन्यथा अणु
				icm_मुक्त_unplugged_children(port->remote->sw);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम icm_rescan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा icm *icm = container_of(work, काष्ठा icm, rescan_work.work);
	काष्ठा tb *tb = icm_to_tb(icm);

	mutex_lock(&tb->lock);
	अगर (tb->root_चयन)
		icm_मुक्त_unplugged_children(tb->root_चयन);
	mutex_unlock(&tb->lock);
पूर्ण

अटल व्योम icm_complete(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);

	अगर (tb->nhi->going_away)
		वापस;

	/*
	 * If RTD3 was vetoed beक्रमe we entered प्रणाली suspend allow it
	 * again now beक्रमe driver पढ़ोy is sent. Firmware sends a new RTD3
	 * veto अगर it is still the हाल after we have sent it driver पढ़ोy
	 * command.
	 */
	icm_veto_end(tb);
	icm_unplug_children(tb->root_चयन);

	/*
	 * Now all existing children should be resumed, start events
	 * from ICM to get updated status.
	 */
	__icm_driver_पढ़ोy(tb, शून्य, शून्य, शून्य, शून्य);

	/*
	 * We करो not get notअगरications of devices that have been
	 * unplugged during suspend so schedule rescan to clean them up
	 * अगर any.
	 */
	queue_delayed_work(tb->wq, &icm->rescan_work, msecs_to_jअगरfies(500));
पूर्ण

अटल पूर्णांक icm_runसमय_suspend(काष्ठा tb *tb)
अणु
	nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_DRV_UNLOADS, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक icm_runसमय_suspend_चयन(काष्ठा tb_चयन *sw)
अणु
	अगर (tb_route(sw))
		reinit_completion(&sw->rpm_complete);
	वापस 0;
पूर्ण

अटल पूर्णांक icm_runसमय_resume_चयन(काष्ठा tb_चयन *sw)
अणु
	अगर (tb_route(sw)) अणु
		अगर (!रुको_क्रम_completion_समयout(&sw->rpm_complete,
						 msecs_to_jअगरfies(500))) अणु
			dev_dbg(&sw->dev, "runtime resuming timed out\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक icm_runसमय_resume(काष्ठा tb *tb)
अणु
	/*
	 * We can reuse the same resume functionality than with प्रणाली
	 * suspend.
	 */
	icm_complete(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक icm_start(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);
	पूर्णांक ret;

	अगर (icm->safe_mode)
		tb->root_चयन = tb_चयन_alloc_safe_mode(tb, &tb->dev, 0);
	अन्यथा
		tb->root_चयन = tb_चयन_alloc(tb, &tb->dev, 0);
	अगर (IS_ERR(tb->root_चयन))
		वापस PTR_ERR(tb->root_चयन);

	tb->root_चयन->no_nvm_upgrade = !icm->can_upgrade_nvm;
	tb->root_चयन->rpm = icm->rpm;

	अगर (icm->set_uuid)
		icm->set_uuid(tb);

	ret = tb_चयन_add(tb->root_चयन);
	अगर (ret) अणु
		tb_चयन_put(tb->root_चयन);
		tb->root_चयन = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम icm_stop(काष्ठा tb *tb)
अणु
	काष्ठा icm *icm = tb_priv(tb);

	cancel_delayed_work(&icm->rescan_work);
	tb_चयन_हटाओ(tb->root_चयन);
	tb->root_चयन = शून्य;
	nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_DRV_UNLOADS, 0);
	kमुक्त(icm->last_nvm_auth);
	icm->last_nvm_auth = शून्य;
पूर्ण

अटल पूर्णांक icm_disconnect_pcie_paths(काष्ठा tb *tb)
अणु
	वापस nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_DISCONNECT_PCIE_PATHS, 0);
पूर्ण

अटल व्योम icm_usb4_चयन_nvm_auth_complete(व्योम *data)
अणु
	काष्ठा usb4_चयन_nvm_auth *auth = data;
	काष्ठा icm *icm = auth->icm;
	काष्ठा tb *tb = icm_to_tb(icm);

	tb_dbg(tb, "NVM_AUTH response for %llx flags %#x status %#x\n",
	       get_route(auth->reply.route_hi, auth->reply.route_lo),
	       auth->reply.hdr.flags, auth->reply.status);

	mutex_lock(&tb->lock);
	अगर (WARN_ON(icm->last_nvm_auth))
		kमुक्त(icm->last_nvm_auth);
	icm->last_nvm_auth = auth;
	mutex_unlock(&tb->lock);
पूर्ण

अटल पूर्णांक icm_usb4_चयन_nvm_authenticate(काष्ठा tb *tb, u64 route)
अणु
	काष्ठा usb4_चयन_nvm_auth *auth;
	काष्ठा icm *icm = tb_priv(tb);
	काष्ठा tb_cfg_request *req;
	पूर्णांक ret;

	auth = kzalloc(माप(*auth), GFP_KERNEL);
	अगर (!auth)
		वापस -ENOMEM;

	auth->icm = icm;
	auth->request.hdr.code = ICM_USB4_SWITCH_OP;
	auth->request.route_hi = upper_32_bits(route);
	auth->request.route_lo = lower_32_bits(route);
	auth->request.opcode = USB4_SWITCH_OP_NVM_AUTH;

	req = tb_cfg_request_alloc();
	अगर (!req) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_auth;
	पूर्ण

	req->match = icm_match;
	req->copy = icm_copy;
	req->request = &auth->request;
	req->request_size = माप(auth->request);
	req->request_type = TB_CFG_PKG_ICM_CMD;
	req->response = &auth->reply;
	req->npackets = 1;
	req->response_size = माप(auth->reply);
	req->response_type = TB_CFG_PKG_ICM_RESP;

	tb_dbg(tb, "NVM_AUTH request for %llx\n", route);

	mutex_lock(&icm->request_lock);
	ret = tb_cfg_request(tb->ctl, req, icm_usb4_चयन_nvm_auth_complete,
			     auth);
	mutex_unlock(&icm->request_lock);

	tb_cfg_request_put(req);
	अगर (ret)
		जाओ err_मुक्त_auth;
	वापस 0;

err_मुक्त_auth:
	kमुक्त(auth);
	वापस ret;
पूर्ण

अटल पूर्णांक icm_usb4_चयन_op(काष्ठा tb_चयन *sw, u16 opcode, u32 *metadata,
			      u8 *status, स्थिर व्योम *tx_data, माप_प्रकार tx_data_len,
			      व्योम *rx_data, माप_प्रकार rx_data_len)
अणु
	काष्ठा icm_usb4_चयन_op_response reply;
	काष्ठा icm_usb4_चयन_op request;
	काष्ठा tb *tb = sw->tb;
	काष्ठा icm *icm = tb_priv(tb);
	u64 route = tb_route(sw);
	पूर्णांक ret;

	/*
	 * USB4 router operation proxy is supported in firmware अगर the
	 * protocol version is 3 or higher.
	 */
	अगर (icm->proto_version < 3)
		वापस -EOPNOTSUPP;

	/*
	 * NVM_AUTH is a special USB4 proxy operation that करोes not
	 * वापस immediately so handle it separately.
	 */
	अगर (opcode == USB4_SWITCH_OP_NVM_AUTH)
		वापस icm_usb4_चयन_nvm_authenticate(tb, route);

	स_रखो(&request, 0, माप(request));
	request.hdr.code = ICM_USB4_SWITCH_OP;
	request.route_hi = upper_32_bits(route);
	request.route_lo = lower_32_bits(route);
	request.opcode = opcode;
	अगर (metadata)
		request.metadata = *metadata;

	अगर (tx_data_len) अणु
		request.data_len_valid |= ICM_USB4_SWITCH_DATA_VALID;
		अगर (tx_data_len < ARRAY_SIZE(request.data))
			request.data_len_valid =
				tx_data_len & ICM_USB4_SWITCH_DATA_LEN_MASK;
		स_नकल(request.data, tx_data, tx_data_len * माप(u32));
	पूर्ण

	स_रखो(&reply, 0, माप(reply));
	ret = icm_request(tb, &request, माप(request), &reply, माप(reply),
			  1, ICM_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (reply.hdr.flags & ICM_FLAGS_ERROR)
		वापस -EIO;

	अगर (status)
		*status = reply.status;

	अगर (metadata)
		*metadata = reply.metadata;

	अगर (rx_data_len)
		स_नकल(rx_data, reply.data, rx_data_len * माप(u32));

	वापस 0;
पूर्ण

अटल पूर्णांक icm_usb4_चयन_nvm_authenticate_status(काष्ठा tb_चयन *sw,
						   u32 *status)
अणु
	काष्ठा usb4_चयन_nvm_auth *auth;
	काष्ठा tb *tb = sw->tb;
	काष्ठा icm *icm = tb_priv(tb);
	पूर्णांक ret = 0;

	अगर (icm->proto_version < 3)
		वापस -EOPNOTSUPP;

	auth = icm->last_nvm_auth;
	icm->last_nvm_auth = शून्य;

	अगर (auth && auth->reply.route_hi == sw->config.route_hi &&
	    auth->reply.route_lo == sw->config.route_lo) अणु
		tb_dbg(tb, "NVM_AUTH found for %llx flags %#x status %#x\n",
		       tb_route(sw), auth->reply.hdr.flags, auth->reply.status);
		अगर (auth->reply.hdr.flags & ICM_FLAGS_ERROR)
			ret = -EIO;
		अन्यथा
			*status = auth->reply.status;
	पूर्ण अन्यथा अणु
		*status = 0;
	पूर्ण

	kमुक्त(auth);
	वापस ret;
पूर्ण

/* Falcon Ridge */
अटल स्थिर काष्ठा tb_cm_ops icm_fr_ops = अणु
	.driver_पढ़ोy = icm_driver_पढ़ोy,
	.start = icm_start,
	.stop = icm_stop,
	.suspend = icm_suspend,
	.complete = icm_complete,
	.handle_event = icm_handle_event,
	.approve_चयन = icm_fr_approve_चयन,
	.add_चयन_key = icm_fr_add_चयन_key,
	.challenge_चयन_key = icm_fr_challenge_चयन_key,
	.disconnect_pcie_paths = icm_disconnect_pcie_paths,
	.approve_xकरोमुख्य_paths = icm_fr_approve_xकरोमुख्य_paths,
	.disconnect_xकरोमुख्य_paths = icm_fr_disconnect_xकरोमुख्य_paths,
पूर्ण;

/* Alpine Ridge */
अटल स्थिर काष्ठा tb_cm_ops icm_ar_ops = अणु
	.driver_पढ़ोy = icm_driver_पढ़ोy,
	.start = icm_start,
	.stop = icm_stop,
	.suspend = icm_suspend,
	.complete = icm_complete,
	.runसमय_suspend = icm_runसमय_suspend,
	.runसमय_resume = icm_runसमय_resume,
	.runसमय_suspend_चयन = icm_runसमय_suspend_चयन,
	.runसमय_resume_चयन = icm_runसमय_resume_चयन,
	.handle_event = icm_handle_event,
	.get_boot_acl = icm_ar_get_boot_acl,
	.set_boot_acl = icm_ar_set_boot_acl,
	.approve_चयन = icm_fr_approve_चयन,
	.add_चयन_key = icm_fr_add_चयन_key,
	.challenge_चयन_key = icm_fr_challenge_चयन_key,
	.disconnect_pcie_paths = icm_disconnect_pcie_paths,
	.approve_xकरोमुख्य_paths = icm_fr_approve_xकरोमुख्य_paths,
	.disconnect_xकरोमुख्य_paths = icm_fr_disconnect_xकरोमुख्य_paths,
पूर्ण;

/* Titan Ridge */
अटल स्थिर काष्ठा tb_cm_ops icm_tr_ops = अणु
	.driver_पढ़ोy = icm_driver_पढ़ोy,
	.start = icm_start,
	.stop = icm_stop,
	.suspend = icm_suspend,
	.complete = icm_complete,
	.runसमय_suspend = icm_runसमय_suspend,
	.runसमय_resume = icm_runसमय_resume,
	.runसमय_suspend_चयन = icm_runसमय_suspend_चयन,
	.runसमय_resume_चयन = icm_runसमय_resume_चयन,
	.handle_event = icm_handle_event,
	.get_boot_acl = icm_ar_get_boot_acl,
	.set_boot_acl = icm_ar_set_boot_acl,
	.approve_चयन = icm_tr_approve_चयन,
	.add_चयन_key = icm_tr_add_चयन_key,
	.challenge_चयन_key = icm_tr_challenge_चयन_key,
	.disconnect_pcie_paths = icm_disconnect_pcie_paths,
	.approve_xकरोमुख्य_paths = icm_tr_approve_xकरोमुख्य_paths,
	.disconnect_xकरोमुख्य_paths = icm_tr_disconnect_xकरोमुख्य_paths,
	.usb4_चयन_op = icm_usb4_चयन_op,
	.usb4_चयन_nvm_authenticate_status =
		icm_usb4_चयन_nvm_authenticate_status,
पूर्ण;

/* Ice Lake */
अटल स्थिर काष्ठा tb_cm_ops icm_icl_ops = अणु
	.driver_पढ़ोy = icm_driver_पढ़ोy,
	.start = icm_start,
	.stop = icm_stop,
	.complete = icm_complete,
	.runसमय_suspend = icm_runसमय_suspend,
	.runसमय_resume = icm_runसमय_resume,
	.handle_event = icm_handle_event,
	.approve_xकरोमुख्य_paths = icm_tr_approve_xकरोमुख्य_paths,
	.disconnect_xकरोमुख्य_paths = icm_tr_disconnect_xकरोमुख्य_paths,
	.usb4_चयन_op = icm_usb4_चयन_op,
	.usb4_चयन_nvm_authenticate_status =
		icm_usb4_चयन_nvm_authenticate_status,
पूर्ण;

काष्ठा tb *icm_probe(काष्ठा tb_nhi *nhi)
अणु
	काष्ठा icm *icm;
	काष्ठा tb *tb;

	tb = tb_करोमुख्य_alloc(nhi, ICM_TIMEOUT, माप(काष्ठा icm));
	अगर (!tb)
		वापस शून्य;

	icm = tb_priv(tb);
	INIT_DELAYED_WORK(&icm->rescan_work, icm_rescan_work);
	mutex_init(&icm->request_lock);

	चयन (nhi->pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_2C_NHI:
	हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_4C_NHI:
		icm->can_upgrade_nvm = true;
		icm->is_supported = icm_fr_is_supported;
		icm->get_route = icm_fr_get_route;
		icm->save_devices = icm_fr_save_devices;
		icm->driver_पढ़ोy = icm_fr_driver_पढ़ोy;
		icm->device_connected = icm_fr_device_connected;
		icm->device_disconnected = icm_fr_device_disconnected;
		icm->xकरोमुख्य_connected = icm_fr_xकरोमुख्य_connected;
		icm->xकरोमुख्य_disconnected = icm_fr_xकरोमुख्य_disconnected;
		tb->cm_ops = &icm_fr_ops;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_NHI:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_NHI:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_NHI:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_NHI:
	हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_NHI:
		icm->max_boot_acl = ICM_AR_PREBOOT_ACL_ENTRIES;
		/*
		 * NVM upgrade has not been tested on Apple प्रणालीs and
		 * they करोn't provide images खुलाly either. To be on
		 * the safe side prevent root चयन NVM upgrade on Macs
		 * क्रम now.
		 */
		icm->can_upgrade_nvm = !x86_apple_machine;
		icm->is_supported = icm_ar_is_supported;
		icm->cio_reset = icm_ar_cio_reset;
		icm->get_mode = icm_ar_get_mode;
		icm->get_route = icm_ar_get_route;
		icm->save_devices = icm_fr_save_devices;
		icm->driver_पढ़ोy = icm_ar_driver_पढ़ोy;
		icm->device_connected = icm_fr_device_connected;
		icm->device_disconnected = icm_fr_device_disconnected;
		icm->xकरोमुख्य_connected = icm_fr_xकरोमुख्य_connected;
		icm->xकरोमुख्य_disconnected = icm_fr_xकरोमुख्य_disconnected;
		tb->cm_ops = &icm_ar_ops;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_NHI:
	हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_NHI:
		icm->max_boot_acl = ICM_AR_PREBOOT_ACL_ENTRIES;
		icm->can_upgrade_nvm = !x86_apple_machine;
		icm->is_supported = icm_ar_is_supported;
		icm->cio_reset = icm_tr_cio_reset;
		icm->get_mode = icm_ar_get_mode;
		icm->driver_पढ़ोy = icm_tr_driver_पढ़ोy;
		icm->device_connected = icm_tr_device_connected;
		icm->device_disconnected = icm_tr_device_disconnected;
		icm->xकरोमुख्य_connected = icm_tr_xकरोमुख्य_connected;
		icm->xकरोमुख्य_disconnected = icm_tr_xकरोमुख्य_disconnected;
		tb->cm_ops = &icm_tr_ops;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_ICL_NHI0:
	हाल PCI_DEVICE_ID_INTEL_ICL_NHI1:
		icm->is_supported = icm_fr_is_supported;
		icm->driver_पढ़ोy = icm_icl_driver_पढ़ोy;
		icm->set_uuid = icm_icl_set_uuid;
		icm->device_connected = icm_icl_device_connected;
		icm->device_disconnected = icm_tr_device_disconnected;
		icm->xकरोमुख्य_connected = icm_tr_xकरोमुख्य_connected;
		icm->xकरोमुख्य_disconnected = icm_tr_xकरोमुख्य_disconnected;
		icm->rtd3_veto = icm_icl_rtd3_veto;
		tb->cm_ops = &icm_icl_ops;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_TGL_NHI0:
	हाल PCI_DEVICE_ID_INTEL_TGL_NHI1:
	हाल PCI_DEVICE_ID_INTEL_TGL_H_NHI0:
	हाल PCI_DEVICE_ID_INTEL_TGL_H_NHI1:
		icm->is_supported = icm_tgl_is_supported;
		icm->driver_पढ़ोy = icm_icl_driver_पढ़ोy;
		icm->set_uuid = icm_icl_set_uuid;
		icm->device_connected = icm_icl_device_connected;
		icm->device_disconnected = icm_tr_device_disconnected;
		icm->xकरोमुख्य_connected = icm_tr_xकरोमुख्य_connected;
		icm->xकरोमुख्य_disconnected = icm_tr_xकरोमुख्य_disconnected;
		icm->rtd3_veto = icm_icl_rtd3_veto;
		tb->cm_ops = &icm_icl_ops;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_MAPLE_RIDGE_4C_NHI:
		icm->is_supported = icm_tgl_is_supported;
		icm->get_mode = icm_ar_get_mode;
		icm->driver_पढ़ोy = icm_tr_driver_पढ़ोy;
		icm->device_connected = icm_tr_device_connected;
		icm->device_disconnected = icm_tr_device_disconnected;
		icm->xकरोमुख्य_connected = icm_tr_xकरोमुख्य_connected;
		icm->xकरोमुख्य_disconnected = icm_tr_xकरोमुख्य_disconnected;
		tb->cm_ops = &icm_tr_ops;
		अवरोध;
	पूर्ण

	अगर (!icm->is_supported || !icm->is_supported(tb)) अणु
		dev_dbg(&nhi->pdev->dev, "ICM not supported on this controller\n");
		tb_करोमुख्य_put(tb);
		वापस शून्य;
	पूर्ण

	tb_dbg(tb, "using firmware connection manager\n");

	वापस tb;
पूर्ण
