<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/pid.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/mutex.h>
#समावेश <net/netlink.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/rdma_netlink.h>

#समावेश "core_priv.h"
#समावेश "cma_priv.h"
#समावेश "restrack.h"
#समावेश "uverbs.h"

प्रकार पूर्णांक (*res_fill_func_t)(काष्ठा sk_buff*, bool,
			       काष्ठा rdma_restrack_entry*, uपूर्णांक32_t);

/*
 * Sort array elements by the netlink attribute name
 */
अटल स्थिर काष्ठा nla_policy nldev_policy[RDMA_NLDEV_ATTR_MAX] = अणु
	[RDMA_NLDEV_ATTR_CHARDEV]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_CHARDEV_ABI]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_CHARDEV_NAME]		= अणु .type = NLA_NUL_STRING,
					.len = RDMA_NLDEV_ATTR_EMPTY_STRING पूर्ण,
	[RDMA_NLDEV_ATTR_CHARDEV_TYPE]		= अणु .type = NLA_NUL_STRING,
					.len = RDMA_NLDEV_ATTR_CHARDEV_TYPE_SIZE पूर्ण,
	[RDMA_NLDEV_ATTR_DEV_DIM]               = अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_DEV_INDEX]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_DEV_NAME]		= अणु .type = NLA_NUL_STRING,
					.len = IB_DEVICE_NAME_MAX पूर्ण,
	[RDMA_NLDEV_ATTR_DEV_NODE_TYPE]		= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_DEV_PROTOCOL]		= अणु .type = NLA_NUL_STRING,
					.len = RDMA_NLDEV_ATTR_EMPTY_STRING पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER_ENTRY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER_PRINT_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER_STRING]		= अणु .type = NLA_NUL_STRING,
					.len = RDMA_NLDEV_ATTR_EMPTY_STRING पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER_S32]		= अणु .type = NLA_S32 पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER_S64]		= अणु .type = NLA_S64 पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER_U32]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_DRIVER_U64]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_FW_VERSION]		= अणु .type = NLA_NUL_STRING,
					.len = RDMA_NLDEV_ATTR_EMPTY_STRING पूर्ण,
	[RDMA_NLDEV_ATTR_LID]			= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_LINK_TYPE]		= अणु .type = NLA_NUL_STRING,
					.len = IFNAMSIZ पूर्ण,
	[RDMA_NLDEV_ATTR_LMC]			= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_NDEV_INDEX]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_NDEV_NAME]		= अणु .type = NLA_NUL_STRING,
					.len = IFNAMSIZ पूर्ण,
	[RDMA_NLDEV_ATTR_NODE_GUID]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_PORT_INDEX]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_PORT_PHYS_STATE]	= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_PORT_STATE]		= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CM_ID]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CM_IDN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CM_ID_ENTRY]	= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CQ]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CQE]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CQN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CQ_ENTRY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CTX]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CTXN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_CTX_ENTRY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_DST_ADDR]		= अणु
			.len = माप(काष्ठा __kernel_sockaddr_storage) पूर्ण,
	[RDMA_NLDEV_ATTR_RES_IOVA]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_KERN_NAME]		= अणु .type = NLA_NUL_STRING,
					.len = RDMA_NLDEV_ATTR_EMPTY_STRING पूर्ण,
	[RDMA_NLDEV_ATTR_RES_LKEY]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_LOCAL_DMA_LKEY]	= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_LQPN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_MR]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_MRLEN]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_MRN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_MR_ENTRY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_PATH_MIG_STATE]	= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_PD]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_PDN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_PD_ENTRY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_PID]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_POLL_CTX]		= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_PS]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_QP]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_QP_ENTRY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_RAW]		= अणु .type = NLA_BINARY पूर्ण,
	[RDMA_NLDEV_ATTR_RES_RKEY]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_RQPN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_RQ_PSN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SQ_PSN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SRC_ADDR]		= अणु
			.len = माप(काष्ठा __kernel_sockaddr_storage) पूर्ण,
	[RDMA_NLDEV_ATTR_RES_STATE]		= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SUMMARY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY]	= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_CURR]= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_NAME]= अणु .type = NLA_NUL_STRING,
					.len = RDMA_NLDEV_ATTR_EMPTY_STRING पूर्ण,
	[RDMA_NLDEV_ATTR_RES_TYPE]		= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_UNSAFE_GLOBAL_RKEY]= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_USECNT]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SRQ]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SRQN]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_RES_SRQ_ENTRY]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_MIN_RANGE]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_MAX_RANGE]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_SM_LID]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_SUBNET_PREFIX]		= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_AUTO_MODE_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_MODE]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_RES]		= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_COUNTER]		= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_COUNTER_ENTRY]	= अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_COUNTER_ID]       = अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_HWCOUNTERS]       = अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_HWCOUNTER_ENTRY]  = अणु .type = NLA_NESTED पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_HWCOUNTER_ENTRY_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[RDMA_NLDEV_ATTR_STAT_HWCOUNTER_ENTRY_VALUE] = अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_SYS_IMAGE_GUID]	= अणु .type = NLA_U64 पूर्ण,
	[RDMA_NLDEV_ATTR_UVERBS_DRIVER_ID]	= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_NET_NS_FD]			= अणु .type = NLA_U32 पूर्ण,
	[RDMA_NLDEV_SYS_ATTR_NETNS_MODE]	= अणु .type = NLA_U8 पूर्ण,
	[RDMA_NLDEV_SYS_ATTR_COPY_ON_FORK]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक put_driver_name_prपूर्णांक_type(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
				      क्रमागत rdma_nldev_prपूर्णांक_type prपूर्णांक_type)
अणु
	अगर (nla_put_string(msg, RDMA_NLDEV_ATTR_DRIVER_STRING, name))
		वापस -EMSGSIZE;
	अगर (prपूर्णांक_type != RDMA_NLDEV_PRINT_TYPE_UNSPEC &&
	    nla_put_u8(msg, RDMA_NLDEV_ATTR_DRIVER_PRINT_TYPE, prपूर्णांक_type))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक _rdma_nl_put_driver_u32(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
				   क्रमागत rdma_nldev_prपूर्णांक_type prपूर्णांक_type,
				   u32 value)
अणु
	अगर (put_driver_name_prपूर्णांक_type(msg, name, prपूर्णांक_type))
		वापस -EMSGSIZE;
	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_DRIVER_U32, value))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक _rdma_nl_put_driver_u64(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
				   क्रमागत rdma_nldev_prपूर्णांक_type prपूर्णांक_type,
				   u64 value)
अणु
	अगर (put_driver_name_prपूर्णांक_type(msg, name, prपूर्णांक_type))
		वापस -EMSGSIZE;
	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_DRIVER_U64, value,
			      RDMA_NLDEV_ATTR_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

पूर्णांक rdma_nl_put_driver_string(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
			      स्थिर अक्षर *str)
अणु
	अगर (put_driver_name_prपूर्णांक_type(msg, name,
				       RDMA_NLDEV_PRINT_TYPE_UNSPEC))
		वापस -EMSGSIZE;
	अगर (nla_put_string(msg, RDMA_NLDEV_ATTR_DRIVER_STRING, str))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rdma_nl_put_driver_string);

पूर्णांक rdma_nl_put_driver_u32(काष्ठा sk_buff *msg, स्थिर अक्षर *name, u32 value)
अणु
	वापस _rdma_nl_put_driver_u32(msg, name, RDMA_NLDEV_PRINT_TYPE_UNSPEC,
				       value);
पूर्ण
EXPORT_SYMBOL(rdma_nl_put_driver_u32);

पूर्णांक rdma_nl_put_driver_u32_hex(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
			       u32 value)
अणु
	वापस _rdma_nl_put_driver_u32(msg, name, RDMA_NLDEV_PRINT_TYPE_HEX,
				       value);
पूर्ण
EXPORT_SYMBOL(rdma_nl_put_driver_u32_hex);

पूर्णांक rdma_nl_put_driver_u64(काष्ठा sk_buff *msg, स्थिर अक्षर *name, u64 value)
अणु
	वापस _rdma_nl_put_driver_u64(msg, name, RDMA_NLDEV_PRINT_TYPE_UNSPEC,
				       value);
पूर्ण
EXPORT_SYMBOL(rdma_nl_put_driver_u64);

पूर्णांक rdma_nl_put_driver_u64_hex(काष्ठा sk_buff *msg, स्थिर अक्षर *name, u64 value)
अणु
	वापस _rdma_nl_put_driver_u64(msg, name, RDMA_NLDEV_PRINT_TYPE_HEX,
				       value);
पूर्ण
EXPORT_SYMBOL(rdma_nl_put_driver_u64_hex);

अटल पूर्णांक fill_nldev_handle(काष्ठा sk_buff *msg, काष्ठा ib_device *device)
अणु
	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_DEV_INDEX, device->index))
		वापस -EMSGSIZE;
	अगर (nla_put_string(msg, RDMA_NLDEV_ATTR_DEV_NAME,
			   dev_name(&device->dev)))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक fill_dev_info(काष्ठा sk_buff *msg, काष्ठा ib_device *device)
अणु
	अक्षर fw[IB_FW_VERSION_NAME_MAX];
	पूर्णांक ret = 0;
	u32 port;

	अगर (fill_nldev_handle(msg, device))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, rdma_end_port(device)))
		वापस -EMSGSIZE;

	BUILD_BUG_ON(माप(device->attrs.device_cap_flags) != माप(u64));
	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CAP_FLAGS,
			      device->attrs.device_cap_flags,
			      RDMA_NLDEV_ATTR_PAD))
		वापस -EMSGSIZE;

	ib_get_device_fw_str(device, fw);
	/* Device without FW has म_माप(fw) = 0 */
	अगर (म_माप(fw) && nla_put_string(msg, RDMA_NLDEV_ATTR_FW_VERSION, fw))
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_NODE_GUID,
			      be64_to_cpu(device->node_guid),
			      RDMA_NLDEV_ATTR_PAD))
		वापस -EMSGSIZE;
	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_SYS_IMAGE_GUID,
			      be64_to_cpu(device->attrs.sys_image_guid),
			      RDMA_NLDEV_ATTR_PAD))
		वापस -EMSGSIZE;
	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_DEV_NODE_TYPE, device->node_type))
		वापस -EMSGSIZE;
	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_DEV_DIM, device->use_cq_dim))
		वापस -EMSGSIZE;

	/*
	 * Link type is determined on first port and mlx4 device
	 * which can potentially have two dअगरferent link type क्रम the same
	 * IB device is considered as better to be aव्योमed in the future,
	 */
	port = rdma_start_port(device);
	अगर (rdma_cap_opa_mad(device, port))
		ret = nla_put_string(msg, RDMA_NLDEV_ATTR_DEV_PROTOCOL, "opa");
	अन्यथा अगर (rdma_protocol_ib(device, port))
		ret = nla_put_string(msg, RDMA_NLDEV_ATTR_DEV_PROTOCOL, "ib");
	अन्यथा अगर (rdma_protocol_iwarp(device, port))
		ret = nla_put_string(msg, RDMA_NLDEV_ATTR_DEV_PROTOCOL, "iw");
	अन्यथा अगर (rdma_protocol_roce(device, port))
		ret = nla_put_string(msg, RDMA_NLDEV_ATTR_DEV_PROTOCOL, "roce");
	अन्यथा अगर (rdma_protocol_usnic(device, port))
		ret = nla_put_string(msg, RDMA_NLDEV_ATTR_DEV_PROTOCOL,
				     "usnic");
	वापस ret;
पूर्ण

अटल पूर्णांक fill_port_info(काष्ठा sk_buff *msg,
			  काष्ठा ib_device *device, u32 port,
			  स्थिर काष्ठा net *net)
अणु
	काष्ठा net_device *netdev = शून्य;
	काष्ठा ib_port_attr attr;
	पूर्णांक ret;
	u64 cap_flags = 0;

	अगर (fill_nldev_handle(msg, device))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port))
		वापस -EMSGSIZE;

	ret = ib_query_port(device, port, &attr);
	अगर (ret)
		वापस ret;

	अगर (rdma_protocol_ib(device, port)) अणु
		BUILD_BUG_ON((माप(attr.port_cap_flags) +
				माप(attr.port_cap_flags2)) > माप(u64));
		cap_flags = attr.port_cap_flags |
			((u64)attr.port_cap_flags2 << 32);
		अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CAP_FLAGS,
				      cap_flags, RDMA_NLDEV_ATTR_PAD))
			वापस -EMSGSIZE;
		अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_SUBNET_PREFIX,
				      attr.subnet_prefix, RDMA_NLDEV_ATTR_PAD))
			वापस -EMSGSIZE;
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_LID, attr.lid))
			वापस -EMSGSIZE;
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_SM_LID, attr.sm_lid))
			वापस -EMSGSIZE;
		अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_LMC, attr.lmc))
			वापस -EMSGSIZE;
	पूर्ण
	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_PORT_STATE, attr.state))
		वापस -EMSGSIZE;
	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_PORT_PHYS_STATE, attr.phys_state))
		वापस -EMSGSIZE;

	netdev = ib_device_get_netdev(device, port);
	अगर (netdev && net_eq(dev_net(netdev), net)) अणु
		ret = nla_put_u32(msg,
				  RDMA_NLDEV_ATTR_NDEV_INDEX, netdev->अगरindex);
		अगर (ret)
			जाओ out;
		ret = nla_put_string(msg,
				     RDMA_NLDEV_ATTR_NDEV_NAME, netdev->name);
	पूर्ण

out:
	अगर (netdev)
		dev_put(netdev);
	वापस ret;
पूर्ण

अटल पूर्णांक fill_res_info_entry(काष्ठा sk_buff *msg,
			       स्थिर अक्षर *name, u64 curr)
अणु
	काष्ठा nlattr *entry_attr;

	entry_attr = nla_nest_start_noflag(msg,
					   RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY);
	अगर (!entry_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_string(msg, RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_NAME, name))
		जाओ err;
	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_CURR, curr,
			      RDMA_NLDEV_ATTR_PAD))
		जाओ err;

	nla_nest_end(msg, entry_attr);
	वापस 0;

err:
	nla_nest_cancel(msg, entry_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_info(काष्ठा sk_buff *msg, काष्ठा ib_device *device)
अणु
	अटल स्थिर अक्षर * स्थिर names[RDMA_RESTRACK_MAX] = अणु
		[RDMA_RESTRACK_PD] = "pd",
		[RDMA_RESTRACK_CQ] = "cq",
		[RDMA_RESTRACK_QP] = "qp",
		[RDMA_RESTRACK_CM_ID] = "cm_id",
		[RDMA_RESTRACK_MR] = "mr",
		[RDMA_RESTRACK_CTX] = "ctx",
		[RDMA_RESTRACK_SRQ] = "srq",
	पूर्ण;

	काष्ठा nlattr *table_attr;
	पूर्णांक ret, i, curr;

	अगर (fill_nldev_handle(msg, device))
		वापस -EMSGSIZE;

	table_attr = nla_nest_start_noflag(msg, RDMA_NLDEV_ATTR_RES_SUMMARY);
	अगर (!table_attr)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < RDMA_RESTRACK_MAX; i++) अणु
		अगर (!names[i])
			जारी;
		curr = rdma_restrack_count(device, i);
		ret = fill_res_info_entry(msg, names[i], curr);
		अगर (ret)
			जाओ err;
	पूर्ण

	nla_nest_end(msg, table_attr);
	वापस 0;

err:
	nla_nest_cancel(msg, table_attr);
	वापस ret;
पूर्ण

अटल पूर्णांक fill_res_name_pid(काष्ठा sk_buff *msg,
			     काष्ठा rdma_restrack_entry *res)
अणु
	पूर्णांक err = 0;

	/*
	 * For user resources, user is should पढ़ो /proc/PID/comm to get the
	 * name of the task file.
	 */
	अगर (rdma_is_kernel_res(res)) अणु
		err = nla_put_string(msg, RDMA_NLDEV_ATTR_RES_KERN_NAME,
				     res->kern_name);
	पूर्ण अन्यथा अणु
		pid_t pid;

		pid = task_pid_vnr(res->task);
		/*
		 * Task is dead and in zombie state.
		 * There is no need to prपूर्णांक PID anymore.
		 */
		अगर (pid)
			/*
			 * This part is racy, task can be समाप्तed and PID will
			 * be zero right here but it is ok, next query won't
			 * वापस PID. We करोn't promise real-समय reflection
			 * of SW objects.
			 */
			err = nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_PID, pid);
	पूर्ण

	वापस err ? -EMSGSIZE : 0;
पूर्ण

अटल पूर्णांक fill_res_qp_entry_query(काष्ठा sk_buff *msg,
				   काष्ठा rdma_restrack_entry *res,
				   काष्ठा ib_device *dev,
				   काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_qp_init_attr qp_init_attr;
	काष्ठा ib_qp_attr qp_attr;
	पूर्णांक ret;

	ret = ib_query_qp(qp, &qp_attr, 0, &qp_init_attr);
	अगर (ret)
		वापस ret;

	अगर (qp->qp_type == IB_QPT_RC || qp->qp_type == IB_QPT_UC) अणु
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_RQPN,
				qp_attr.dest_qp_num))
			जाओ err;
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_RQ_PSN,
				qp_attr.rq_psn))
			जाओ err;
	पूर्ण

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_SQ_PSN, qp_attr.sq_psn))
		जाओ err;

	अगर (qp->qp_type == IB_QPT_RC || qp->qp_type == IB_QPT_UC ||
	    qp->qp_type == IB_QPT_XRC_INI || qp->qp_type == IB_QPT_XRC_TGT) अणु
		अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_PATH_MIG_STATE,
			       qp_attr.path_mig_state))
			जाओ err;
	पूर्ण
	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_TYPE, qp->qp_type))
		जाओ err;
	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_STATE, qp_attr.qp_state))
		जाओ err;

	अगर (dev->ops.fill_res_qp_entry)
		वापस dev->ops.fill_res_qp_entry(msg, qp);
	वापस 0;

err:	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_qp_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
			     काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_qp *qp = container_of(res, काष्ठा ib_qp, res);
	काष्ठा ib_device *dev = qp->device;
	पूर्णांक ret;

	अगर (port && port != qp->port)
		वापस -EAGAIN;

	/* In create_qp() port is not set yet */
	अगर (qp->port && nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, qp->port))
		वापस -EINVAL;

	ret = nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LQPN, qp->qp_num);
	अगर (ret)
		वापस -EMSGSIZE;

	अगर (!rdma_is_kernel_res(res) &&
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_PDN, qp->pd->res.id))
		वापस -EMSGSIZE;

	ret = fill_res_name_pid(msg, res);
	अगर (ret)
		वापस -EMSGSIZE;

	वापस fill_res_qp_entry_query(msg, res, dev, qp);
पूर्ण

अटल पूर्णांक fill_res_qp_raw_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
				 काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_qp *qp = container_of(res, काष्ठा ib_qp, res);
	काष्ठा ib_device *dev = qp->device;

	अगर (port && port != qp->port)
		वापस -EAGAIN;
	अगर (!dev->ops.fill_res_qp_entry_raw)
		वापस -EINVAL;
	वापस dev->ops.fill_res_qp_entry_raw(msg, qp);
पूर्ण

अटल पूर्णांक fill_res_cm_id_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
				काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा rdma_id_निजी *id_priv =
				container_of(res, काष्ठा rdma_id_निजी, res);
	काष्ठा ib_device *dev = id_priv->id.device;
	काष्ठा rdma_cm_id *cm_id = &id_priv->id;

	अगर (port && port != cm_id->port_num)
		वापस 0;

	अगर (cm_id->port_num &&
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, cm_id->port_num))
		जाओ err;

	अगर (id_priv->qp_num) अणु
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LQPN, id_priv->qp_num))
			जाओ err;
		अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_TYPE, cm_id->qp_type))
			जाओ err;
	पूर्ण

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_PS, cm_id->ps))
		जाओ err;

	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_STATE, id_priv->state))
		जाओ err;

	अगर (cm_id->route.addr.src_addr.ss_family &&
	    nla_put(msg, RDMA_NLDEV_ATTR_RES_SRC_ADDR,
		    माप(cm_id->route.addr.src_addr),
		    &cm_id->route.addr.src_addr))
		जाओ err;
	अगर (cm_id->route.addr.dst_addr.ss_family &&
	    nla_put(msg, RDMA_NLDEV_ATTR_RES_DST_ADDR,
		    माप(cm_id->route.addr.dst_addr),
		    &cm_id->route.addr.dst_addr))
		जाओ err;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_CM_IDN, res->id))
		जाओ err;

	अगर (fill_res_name_pid(msg, res))
		जाओ err;

	अगर (dev->ops.fill_res_cm_id_entry)
		वापस dev->ops.fill_res_cm_id_entry(msg, cm_id);
	वापस 0;

err: वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_cq_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
			     काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_cq *cq = container_of(res, काष्ठा ib_cq, res);
	काष्ठा ib_device *dev = cq->device;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_CQE, cq->cqe))
		वापस -EMSGSIZE;
	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_RES_USECNT,
			      atomic_पढ़ो(&cq->usecnt), RDMA_NLDEV_ATTR_PAD))
		वापस -EMSGSIZE;

	/* Poll context is only valid क्रम kernel CQs */
	अगर (rdma_is_kernel_res(res) &&
	    nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_POLL_CTX, cq->poll_ctx))
		वापस -EMSGSIZE;

	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_DEV_DIM, (cq->dim != शून्य)))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_CQN, res->id))
		वापस -EMSGSIZE;
	अगर (!rdma_is_kernel_res(res) &&
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_CTXN,
			cq->uobject->uevent.uobject.context->res.id))
		वापस -EMSGSIZE;

	अगर (fill_res_name_pid(msg, res))
		वापस -EMSGSIZE;

	वापस (dev->ops.fill_res_cq_entry) ?
		dev->ops.fill_res_cq_entry(msg, cq) : 0;
पूर्ण

अटल पूर्णांक fill_res_cq_raw_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
				 काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_cq *cq = container_of(res, काष्ठा ib_cq, res);
	काष्ठा ib_device *dev = cq->device;

	अगर (!dev->ops.fill_res_cq_entry_raw)
		वापस -EINVAL;
	वापस dev->ops.fill_res_cq_entry_raw(msg, cq);
पूर्ण

अटल पूर्णांक fill_res_mr_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
			     काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_mr *mr = container_of(res, काष्ठा ib_mr, res);
	काष्ठा ib_device *dev = mr->pd->device;

	अगर (has_cap_net_admin) अणु
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_RKEY, mr->rkey))
			वापस -EMSGSIZE;
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LKEY, mr->lkey))
			वापस -EMSGSIZE;
	पूर्ण

	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_RES_MRLEN, mr->length,
			      RDMA_NLDEV_ATTR_PAD))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_MRN, res->id))
		वापस -EMSGSIZE;

	अगर (!rdma_is_kernel_res(res) &&
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_PDN, mr->pd->res.id))
		वापस -EMSGSIZE;

	अगर (fill_res_name_pid(msg, res))
		वापस -EMSGSIZE;

	वापस (dev->ops.fill_res_mr_entry) ?
		       dev->ops.fill_res_mr_entry(msg, mr) :
		       0;
पूर्ण

अटल पूर्णांक fill_res_mr_raw_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
				 काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_mr *mr = container_of(res, काष्ठा ib_mr, res);
	काष्ठा ib_device *dev = mr->pd->device;

	अगर (!dev->ops.fill_res_mr_entry_raw)
		वापस -EINVAL;
	वापस dev->ops.fill_res_mr_entry_raw(msg, mr);
पूर्ण

अटल पूर्णांक fill_res_pd_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
			     काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_pd *pd = container_of(res, काष्ठा ib_pd, res);

	अगर (has_cap_net_admin) अणु
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LOCAL_DMA_LKEY,
				pd->local_dma_lkey))
			जाओ err;
		अगर ((pd->flags & IB_PD_UNSAFE_GLOBAL_RKEY) &&
		    nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_UNSAFE_GLOBAL_RKEY,
				pd->unsafe_global_rkey))
			जाओ err;
	पूर्ण
	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_RES_USECNT,
			      atomic_पढ़ो(&pd->usecnt), RDMA_NLDEV_ATTR_PAD))
		जाओ err;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_PDN, res->id))
		जाओ err;

	अगर (!rdma_is_kernel_res(res) &&
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_CTXN,
			pd->uobject->context->res.id))
		जाओ err;

	वापस fill_res_name_pid(msg, res);

err:	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_ctx_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
			      काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_ucontext *ctx = container_of(res, काष्ठा ib_ucontext, res);

	अगर (rdma_is_kernel_res(res))
		वापस 0;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_CTXN, ctx->res.id))
		वापस -EMSGSIZE;

	वापस fill_res_name_pid(msg, res);
पूर्ण

अटल पूर्णांक fill_res_range_qp_entry(काष्ठा sk_buff *msg, uपूर्णांक32_t min_range,
				   uपूर्णांक32_t max_range)
अणु
	काष्ठा nlattr *entry_attr;

	अगर (!min_range)
		वापस 0;

	entry_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_RES_QP_ENTRY);
	अगर (!entry_attr)
		वापस -EMSGSIZE;

	अगर (min_range == max_range) अणु
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LQPN, min_range))
			जाओ err;
	पूर्ण अन्यथा अणु
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_MIN_RANGE, min_range))
			जाओ err;
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_MAX_RANGE, max_range))
			जाओ err;
	पूर्ण
	nla_nest_end(msg, entry_attr);
	वापस 0;

err:
	nla_nest_cancel(msg, entry_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_srq_qps(काष्ठा sk_buff *msg, काष्ठा ib_srq *srq)
अणु
	uपूर्णांक32_t min_range = 0, prev = 0;
	काष्ठा rdma_restrack_entry *res;
	काष्ठा rdma_restrack_root *rt;
	काष्ठा nlattr *table_attr;
	काष्ठा ib_qp *qp = शून्य;
	अचिन्हित दीर्घ id = 0;

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_RES_QP);
	अगर (!table_attr)
		वापस -EMSGSIZE;

	rt = &srq->device->res[RDMA_RESTRACK_QP];
	xa_lock(&rt->xa);
	xa_क्रम_each(&rt->xa, id, res) अणु
		अगर (!rdma_restrack_get(res))
			जारी;

		qp = container_of(res, काष्ठा ib_qp, res);
		अगर (!qp->srq || (qp->srq->res.id != srq->res.id)) अणु
			rdma_restrack_put(res);
			जारी;
		पूर्ण

		अगर (qp->qp_num < prev)
			/* qp_num should be ascending */
			जाओ err_loop;

		अगर (min_range == 0) अणु
			min_range = qp->qp_num;
		पूर्ण अन्यथा अगर (qp->qp_num > (prev + 1)) अणु
			अगर (fill_res_range_qp_entry(msg, min_range, prev))
				जाओ err_loop;

			min_range = qp->qp_num;
		पूर्ण
		prev = qp->qp_num;
		rdma_restrack_put(res);
	पूर्ण

	xa_unlock(&rt->xa);

	अगर (fill_res_range_qp_entry(msg, min_range, prev))
		जाओ err;

	nla_nest_end(msg, table_attr);
	वापस 0;

err_loop:
	rdma_restrack_put(res);
	xa_unlock(&rt->xa);
err:
	nla_nest_cancel(msg, table_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_srq_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
			      काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_srq *srq = container_of(res, काष्ठा ib_srq, res);

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_SRQN, srq->res.id))
		जाओ err;

	अगर (nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_TYPE, srq->srq_type))
		जाओ err;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_PDN, srq->pd->res.id))
		जाओ err;

	अगर (ib_srq_has_cq(srq->srq_type)) अणु
		अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_CQN,
				srq->ext.cq->res.id))
			जाओ err;
	पूर्ण

	अगर (fill_res_srq_qps(msg, srq))
		जाओ err;

	वापस fill_res_name_pid(msg, res);

err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_stat_counter_mode(काष्ठा sk_buff *msg,
				  काष्ठा rdma_counter *counter)
अणु
	काष्ठा rdma_counter_mode *m = &counter->mode;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_MODE, m->mode))
		वापस -EMSGSIZE;

	अगर (m->mode == RDMA_COUNTER_MODE_AUTO) अणु
		अगर ((m->mask & RDMA_COUNTER_MASK_QP_TYPE) &&
		    nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_TYPE, m->param.qp_type))
			वापस -EMSGSIZE;

		अगर ((m->mask & RDMA_COUNTER_MASK_PID) &&
		    fill_res_name_pid(msg, &counter->res))
			वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fill_stat_counter_qp_entry(काष्ठा sk_buff *msg, u32 qpn)
अणु
	काष्ठा nlattr *entry_attr;

	entry_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_RES_QP_ENTRY);
	अगर (!entry_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LQPN, qpn))
		जाओ err;

	nla_nest_end(msg, entry_attr);
	वापस 0;

err:
	nla_nest_cancel(msg, entry_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_stat_counter_qps(काष्ठा sk_buff *msg,
				 काष्ठा rdma_counter *counter)
अणु
	काष्ठा rdma_restrack_entry *res;
	काष्ठा rdma_restrack_root *rt;
	काष्ठा nlattr *table_attr;
	काष्ठा ib_qp *qp = शून्य;
	अचिन्हित दीर्घ id = 0;
	पूर्णांक ret = 0;

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_RES_QP);

	rt = &counter->device->res[RDMA_RESTRACK_QP];
	xa_lock(&rt->xa);
	xa_क्रम_each(&rt->xa, id, res) अणु
		qp = container_of(res, काष्ठा ib_qp, res);
		अगर (!qp->counter || (qp->counter->id != counter->id))
			जारी;

		ret = fill_stat_counter_qp_entry(msg, qp->qp_num);
		अगर (ret)
			जाओ err;
	पूर्ण

	xa_unlock(&rt->xa);
	nla_nest_end(msg, table_attr);
	वापस 0;

err:
	xa_unlock(&rt->xa);
	nla_nest_cancel(msg, table_attr);
	वापस ret;
पूर्ण

पूर्णांक rdma_nl_stat_hwcounter_entry(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
				 u64 value)
अणु
	काष्ठा nlattr *entry_attr;

	entry_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_STAT_HWCOUNTER_ENTRY);
	अगर (!entry_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_string(msg, RDMA_NLDEV_ATTR_STAT_HWCOUNTER_ENTRY_NAME,
			   name))
		जाओ err;
	अगर (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_STAT_HWCOUNTER_ENTRY_VALUE,
			      value, RDMA_NLDEV_ATTR_PAD))
		जाओ err;

	nla_nest_end(msg, entry_attr);
	वापस 0;

err:
	nla_nest_cancel(msg, entry_attr);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL(rdma_nl_stat_hwcounter_entry);

अटल पूर्णांक fill_stat_mr_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
			      काष्ठा rdma_restrack_entry *res, uपूर्णांक32_t port)
अणु
	काष्ठा ib_mr *mr = container_of(res, काष्ठा ib_mr, res);
	काष्ठा ib_device *dev = mr->pd->device;

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_MRN, res->id))
		जाओ err;

	अगर (dev->ops.fill_stat_mr_entry)
		वापस dev->ops.fill_stat_mr_entry(msg, mr);
	वापस 0;

err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_stat_counter_hwcounters(काष्ठा sk_buff *msg,
					काष्ठा rdma_counter *counter)
अणु
	काष्ठा rdma_hw_stats *st = counter->stats;
	काष्ठा nlattr *table_attr;
	पूर्णांक i;

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_STAT_HWCOUNTERS);
	अगर (!table_attr)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < st->num_counters; i++)
		अगर (rdma_nl_stat_hwcounter_entry(msg, st->names[i], st->value[i]))
			जाओ err;

	nla_nest_end(msg, table_attr);
	वापस 0;

err:
	nla_nest_cancel(msg, table_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_counter_entry(काष्ठा sk_buff *msg, bool has_cap_net_admin,
				  काष्ठा rdma_restrack_entry *res,
				  uपूर्णांक32_t port)
अणु
	काष्ठा rdma_counter *counter =
		container_of(res, काष्ठा rdma_counter, res);

	अगर (port && port != counter->port)
		वापस -EAGAIN;

	/* Dump it even query failed */
	rdma_counter_query_stats(counter);

	अगर (nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, counter->port) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_COUNTER_ID, counter->id) ||
	    fill_stat_counter_mode(msg, counter) ||
	    fill_stat_counter_qps(msg, counter) ||
	    fill_stat_counter_hwcounters(msg, counter))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक nldev_get_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	काष्ठा sk_buff *msg;
	u32 index;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	अगर (err || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);

	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV, RDMA_NLDEV_CMD_GET),
			0, 0);

	err = fill_dev_info(msg, device);
	अगर (err)
		जाओ err_मुक्त;

	nlmsg_end(msg, nlh);

	ib_device_put(device);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_मुक्त:
	nlmsg_मुक्त(msg);
err:
	ib_device_put(device);
	वापस err;
पूर्ण

अटल पूर्णांक nldev_set_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	u32 index;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	अगर (err || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	अगर (tb[RDMA_NLDEV_ATTR_DEV_NAME]) अणु
		अक्षर name[IB_DEVICE_NAME_MAX] = अणुपूर्ण;

		nla_strscpy(name, tb[RDMA_NLDEV_ATTR_DEV_NAME],
			    IB_DEVICE_NAME_MAX);
		अगर (म_माप(name) == 0) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
		err = ib_device_नाम(device, name);
		जाओ करोne;
	पूर्ण

	अगर (tb[RDMA_NLDEV_NET_NS_FD]) अणु
		u32 ns_fd;

		ns_fd = nla_get_u32(tb[RDMA_NLDEV_NET_NS_FD]);
		err = ib_device_set_netns_put(skb, device, ns_fd);
		जाओ put_करोne;
	पूर्ण

	अगर (tb[RDMA_NLDEV_ATTR_DEV_DIM]) अणु
		u8 use_dim;

		use_dim = nla_get_u8(tb[RDMA_NLDEV_ATTR_DEV_DIM]);
		err = ib_device_set_dim(device,  use_dim);
		जाओ करोne;
	पूर्ण

करोne:
	ib_device_put(device);
put_करोne:
	वापस err;
पूर्ण

अटल पूर्णांक _nldev_get_dumpit(काष्ठा ib_device *device,
			     काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb,
			     अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक start = cb->args[0];
	काष्ठा nlmsghdr *nlh;

	अगर (idx < start)
		वापस 0;

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV, RDMA_NLDEV_CMD_GET),
			0, NLM_F_MULTI);

	अगर (fill_dev_info(skb, device)) अणु
		nlmsg_cancel(skb, nlh);
		जाओ out;
	पूर्ण

	nlmsg_end(skb, nlh);

	idx++;

out:	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nldev_get_dumpit(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	/*
	 * There is no need to take lock, because
	 * we are relying on ib_core's locking.
	 */
	वापस ib_क्रमागत_all_devs(_nldev_get_dumpit, skb, cb);
पूर्ण

अटल पूर्णांक nldev_port_get_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	काष्ठा sk_buff *msg;
	u32 index;
	u32 port;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	अगर (err ||
	    !tb[RDMA_NLDEV_ATTR_DEV_INDEX] ||
	    !tb[RDMA_NLDEV_ATTR_PORT_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
	अगर (!rdma_is_port_valid(device, port)) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV, RDMA_NLDEV_CMD_GET),
			0, 0);

	err = fill_port_info(msg, device, port, sock_net(skb->sk));
	अगर (err)
		जाओ err_मुक्त;

	nlmsg_end(msg, nlh);
	ib_device_put(device);

	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_मुक्त:
	nlmsg_मुक्त(msg);
err:
	ib_device_put(device);
	वापस err;
पूर्ण

अटल पूर्णांक nldev_port_get_dumpit(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	पूर्णांक start = cb->args[0];
	काष्ठा nlmsghdr *nlh;
	u32 idx = 0;
	u32 अगरindex;
	पूर्णांक err;
	अचिन्हित पूर्णांक p;

	err = nlmsg_parse_deprecated(cb->nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, शून्य);
	अगर (err || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		वापस -EINVAL;

	अगरindex = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), अगरindex);
	अगर (!device)
		वापस -EINVAL;

	rdma_क्रम_each_port (device, p) अणु
		/*
		 * The dumpit function वापसs all inक्रमmation from specअगरic
		 * index. This specअगरic index is taken from the netlink
		 * messages request sent by user and it is available
		 * in cb->args[0].
		 *
		 * Usually, the user करोesn't fill this field and it causes
		 * to वापस everything.
		 *
		 */
		अगर (idx < start) अणु
			idx++;
			जारी;
		पूर्ण

		nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq,
				RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
						 RDMA_NLDEV_CMD_PORT_GET),
				0, NLM_F_MULTI);

		अगर (fill_port_info(skb, device, p, sock_net(skb->sk))) अणु
			nlmsg_cancel(skb, nlh);
			जाओ out;
		पूर्ण
		idx++;
		nlmsg_end(skb, nlh);
	पूर्ण

out:
	ib_device_put(device);
	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nldev_res_get_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	काष्ठा sk_buff *msg;
	u32 index;
	पूर्णांक ret;

	ret = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	अगर (ret || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV, RDMA_NLDEV_CMD_RES_GET),
			0, 0);

	ret = fill_res_info(msg, device);
	अगर (ret)
		जाओ err_मुक्त;

	nlmsg_end(msg, nlh);
	ib_device_put(device);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_मुक्त:
	nlmsg_मुक्त(msg);
err:
	ib_device_put(device);
	वापस ret;
पूर्ण

अटल पूर्णांक _nldev_res_get_dumpit(काष्ठा ib_device *device,
				 काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb,
				 अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक start = cb->args[0];
	काष्ठा nlmsghdr *nlh;

	अगर (idx < start)
		वापस 0;

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV, RDMA_NLDEV_CMD_RES_GET),
			0, NLM_F_MULTI);

	अगर (fill_res_info(skb, device)) अणु
		nlmsg_cancel(skb, nlh);
		जाओ out;
	पूर्ण
	nlmsg_end(skb, nlh);

	idx++;

out:
	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nldev_res_get_dumpit(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	वापस ib_क्रमागत_all_devs(_nldev_res_get_dumpit, skb, cb);
पूर्ण

काष्ठा nldev_fill_res_entry अणु
	क्रमागत rdma_nldev_attr nldev_attr;
	u8 flags;
	u32 entry;
	u32 id;
पूर्ण;

क्रमागत nldev_res_flags अणु
	NLDEV_PER_DEV = 1 << 0,
पूर्ण;

अटल स्थिर काष्ठा nldev_fill_res_entry fill_entries[RDMA_RESTRACK_MAX] = अणु
	[RDMA_RESTRACK_QP] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_RES_QP,
		.entry = RDMA_NLDEV_ATTR_RES_QP_ENTRY,
		.id = RDMA_NLDEV_ATTR_RES_LQPN,
	पूर्ण,
	[RDMA_RESTRACK_CM_ID] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_RES_CM_ID,
		.entry = RDMA_NLDEV_ATTR_RES_CM_ID_ENTRY,
		.id = RDMA_NLDEV_ATTR_RES_CM_IDN,
	पूर्ण,
	[RDMA_RESTRACK_CQ] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_RES_CQ,
		.flags = NLDEV_PER_DEV,
		.entry = RDMA_NLDEV_ATTR_RES_CQ_ENTRY,
		.id = RDMA_NLDEV_ATTR_RES_CQN,
	पूर्ण,
	[RDMA_RESTRACK_MR] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_RES_MR,
		.flags = NLDEV_PER_DEV,
		.entry = RDMA_NLDEV_ATTR_RES_MR_ENTRY,
		.id = RDMA_NLDEV_ATTR_RES_MRN,
	पूर्ण,
	[RDMA_RESTRACK_PD] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_RES_PD,
		.flags = NLDEV_PER_DEV,
		.entry = RDMA_NLDEV_ATTR_RES_PD_ENTRY,
		.id = RDMA_NLDEV_ATTR_RES_PDN,
	पूर्ण,
	[RDMA_RESTRACK_COUNTER] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_STAT_COUNTER,
		.entry = RDMA_NLDEV_ATTR_STAT_COUNTER_ENTRY,
		.id = RDMA_NLDEV_ATTR_STAT_COUNTER_ID,
	पूर्ण,
	[RDMA_RESTRACK_CTX] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_RES_CTX,
		.flags = NLDEV_PER_DEV,
		.entry = RDMA_NLDEV_ATTR_RES_CTX_ENTRY,
		.id = RDMA_NLDEV_ATTR_RES_CTXN,
	पूर्ण,
	[RDMA_RESTRACK_SRQ] = अणु
		.nldev_attr = RDMA_NLDEV_ATTR_RES_SRQ,
		.flags = NLDEV_PER_DEV,
		.entry = RDMA_NLDEV_ATTR_RES_SRQ_ENTRY,
		.id = RDMA_NLDEV_ATTR_RES_SRQN,
	पूर्ण,

पूर्ण;

अटल पूर्णांक res_get_common_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack,
			       क्रमागत rdma_restrack_type res_type,
			       res_fill_func_t fill_func)
अणु
	स्थिर काष्ठा nldev_fill_res_entry *fe = &fill_entries[res_type];
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा rdma_restrack_entry *res;
	काष्ठा ib_device *device;
	u32 index, id, port = 0;
	bool has_cap_net_admin;
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	ret = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	अगर (ret || !tb[RDMA_NLDEV_ATTR_DEV_INDEX] || !fe->id || !tb[fe->id])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	अगर (tb[RDMA_NLDEV_ATTR_PORT_INDEX]) अणु
		port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
		अगर (!rdma_is_port_valid(device, port)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर ((port && fe->flags & NLDEV_PER_DEV) ||
	    (!port && ~fe->flags & NLDEV_PER_DEV)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	id = nla_get_u32(tb[fe->id]);
	res = rdma_restrack_get_byid(device, res_type, id);
	अगर (IS_ERR(res)) अणु
		ret = PTR_ERR(res);
		जाओ err;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err_get;
	पूर्ण

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NL_GET_OP(nlh->nlmsg_type)),
			0, 0);

	अगर (fill_nldev_handle(msg, device)) अणु
		ret = -EMSGSIZE;
		जाओ err_मुक्त;
	पूर्ण

	has_cap_net_admin = netlink_capable(skb, CAP_NET_ADMIN);

	ret = fill_func(msg, has_cap_net_admin, res, port);
	अगर (ret)
		जाओ err_मुक्त;

	rdma_restrack_put(res);
	nlmsg_end(msg, nlh);
	ib_device_put(device);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_मुक्त:
	nlmsg_मुक्त(msg);
err_get:
	rdma_restrack_put(res);
err:
	ib_device_put(device);
	वापस ret;
पूर्ण

अटल पूर्णांक res_get_common_dumpit(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb,
				 क्रमागत rdma_restrack_type res_type,
				 res_fill_func_t fill_func)
अणु
	स्थिर काष्ठा nldev_fill_res_entry *fe = &fill_entries[res_type];
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा rdma_restrack_entry *res;
	काष्ठा rdma_restrack_root *rt;
	पूर्णांक err, ret = 0, idx = 0;
	काष्ठा nlattr *table_attr;
	काष्ठा nlattr *entry_attr;
	काष्ठा ib_device *device;
	पूर्णांक start = cb->args[0];
	bool has_cap_net_admin;
	काष्ठा nlmsghdr *nlh;
	अचिन्हित दीर्घ id;
	u32 index, port = 0;
	bool filled = false;

	err = nlmsg_parse_deprecated(cb->nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, शून्य);
	/*
	 * Right now, we are expecting the device index to get res inक्रमmation,
	 * but it is possible to extend this code to वापस all devices in
	 * one shot by checking the existence of RDMA_NLDEV_ATTR_DEV_INDEX.
	 * अगर it करोesn't exist, we will iterate over all devices.
	 *
	 * But it is not needed क्रम now.
	 */
	अगर (err || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	/*
	 * If no PORT_INDEX is supplied, we will वापस all QPs from that device
	 */
	अगर (tb[RDMA_NLDEV_ATTR_PORT_INDEX]) अणु
		port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
		अगर (!rdma_is_port_valid(device, port)) अणु
			ret = -EINVAL;
			जाओ err_index;
		पूर्ण
	पूर्ण

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NL_GET_OP(cb->nlh->nlmsg_type)),
			0, NLM_F_MULTI);

	अगर (fill_nldev_handle(skb, device)) अणु
		ret = -EMSGSIZE;
		जाओ err;
	पूर्ण

	table_attr = nla_nest_start_noflag(skb, fe->nldev_attr);
	अगर (!table_attr) अणु
		ret = -EMSGSIZE;
		जाओ err;
	पूर्ण

	has_cap_net_admin = netlink_capable(cb->skb, CAP_NET_ADMIN);

	rt = &device->res[res_type];
	xa_lock(&rt->xa);
	/*
	 * FIXME: अगर the skip ahead is something common this loop should
	 * use xas_क्रम_each & xas_छोड़ो to optimize, we can have a lot of
	 * objects.
	 */
	xa_क्रम_each(&rt->xa, id, res) अणु
		अगर (idx < start || !rdma_restrack_get(res))
			जाओ next;

		xa_unlock(&rt->xa);

		filled = true;

		entry_attr = nla_nest_start_noflag(skb, fe->entry);
		अगर (!entry_attr) अणु
			ret = -EMSGSIZE;
			rdma_restrack_put(res);
			जाओ msg_full;
		पूर्ण

		ret = fill_func(skb, has_cap_net_admin, res, port);

		rdma_restrack_put(res);

		अगर (ret) अणु
			nla_nest_cancel(skb, entry_attr);
			अगर (ret == -EMSGSIZE)
				जाओ msg_full;
			अगर (ret == -EAGAIN)
				जाओ again;
			जाओ res_err;
		पूर्ण
		nla_nest_end(skb, entry_attr);
again:		xa_lock(&rt->xa);
next:		idx++;
	पूर्ण
	xa_unlock(&rt->xa);

msg_full:
	nla_nest_end(skb, table_attr);
	nlmsg_end(skb, nlh);
	cb->args[0] = idx;

	/*
	 * No more entries to fill, cancel the message and
	 * वापस 0 to mark end of dumpit.
	 */
	अगर (!filled)
		जाओ err;

	ib_device_put(device);
	वापस skb->len;

res_err:
	nla_nest_cancel(skb, table_attr);

err:
	nlmsg_cancel(skb, nlh);

err_index:
	ib_device_put(device);
	वापस ret;
पूर्ण

#घोषणा RES_GET_FUNCS(name, type)                                              \
	अटल पूर्णांक nldev_res_get_##name##_dumpit(काष्ठा sk_buff *skb,          \
						 काष्ठा netlink_callback *cb)  \
	अणु                                                                      \
		वापस res_get_common_dumpit(skb, cb, type,                    \
					     fill_res_##name##_entry);         \
	पूर्ण                                                                      \
	अटल पूर्णांक nldev_res_get_##name##_करोit(काष्ठा sk_buff *skb,            \
					       काष्ठा nlmsghdr *nlh,           \
					       काष्ठा netlink_ext_ack *extack) \
	अणु                                                                      \
		वापस res_get_common_करोit(skb, nlh, extack, type,             \
					   fill_res_##name##_entry);           \
	पूर्ण

RES_GET_FUNCS(qp, RDMA_RESTRACK_QP);
RES_GET_FUNCS(qp_raw, RDMA_RESTRACK_QP);
RES_GET_FUNCS(cm_id, RDMA_RESTRACK_CM_ID);
RES_GET_FUNCS(cq, RDMA_RESTRACK_CQ);
RES_GET_FUNCS(cq_raw, RDMA_RESTRACK_CQ);
RES_GET_FUNCS(pd, RDMA_RESTRACK_PD);
RES_GET_FUNCS(mr, RDMA_RESTRACK_MR);
RES_GET_FUNCS(mr_raw, RDMA_RESTRACK_MR);
RES_GET_FUNCS(counter, RDMA_RESTRACK_COUNTER);
RES_GET_FUNCS(ctx, RDMA_RESTRACK_CTX);
RES_GET_FUNCS(srq, RDMA_RESTRACK_SRQ);

अटल LIST_HEAD(link_ops);
अटल DECLARE_RWSEM(link_ops_rwsem);

अटल स्थिर काष्ठा rdma_link_ops *link_ops_get(स्थिर अक्षर *type)
अणु
	स्थिर काष्ठा rdma_link_ops *ops;

	list_क्रम_each_entry(ops, &link_ops, list) अणु
		अगर (!म_भेद(ops->type, type))
			जाओ out;
	पूर्ण
	ops = शून्य;
out:
	वापस ops;
पूर्ण

व्योम rdma_link_रेजिस्टर(काष्ठा rdma_link_ops *ops)
अणु
	करोwn_ग_लिखो(&link_ops_rwsem);
	अगर (WARN_ON_ONCE(link_ops_get(ops->type)))
		जाओ out;
	list_add(&ops->list, &link_ops);
out:
	up_ग_लिखो(&link_ops_rwsem);
पूर्ण
EXPORT_SYMBOL(rdma_link_रेजिस्टर);

व्योम rdma_link_unरेजिस्टर(काष्ठा rdma_link_ops *ops)
अणु
	करोwn_ग_लिखो(&link_ops_rwsem);
	list_del(&ops->list);
	up_ग_लिखो(&link_ops_rwsem);
पूर्ण
EXPORT_SYMBOL(rdma_link_unरेजिस्टर);

अटल पूर्णांक nldev_newlink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	अक्षर ibdev_name[IB_DEVICE_NAME_MAX];
	स्थिर काष्ठा rdma_link_ops *ops;
	अक्षर ndev_name[IFNAMSIZ];
	काष्ठा net_device *ndev;
	अक्षर type[IFNAMSIZ];
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	अगर (err || !tb[RDMA_NLDEV_ATTR_DEV_NAME] ||
	    !tb[RDMA_NLDEV_ATTR_LINK_TYPE] || !tb[RDMA_NLDEV_ATTR_NDEV_NAME])
		वापस -EINVAL;

	nla_strscpy(ibdev_name, tb[RDMA_NLDEV_ATTR_DEV_NAME],
		    माप(ibdev_name));
	अगर (म_अक्षर(ibdev_name, '%') || म_माप(ibdev_name) == 0)
		वापस -EINVAL;

	nla_strscpy(type, tb[RDMA_NLDEV_ATTR_LINK_TYPE], माप(type));
	nla_strscpy(ndev_name, tb[RDMA_NLDEV_ATTR_NDEV_NAME],
		    माप(ndev_name));

	ndev = dev_get_by_name(sock_net(skb->sk), ndev_name);
	अगर (!ndev)
		वापस -ENODEV;

	करोwn_पढ़ो(&link_ops_rwsem);
	ops = link_ops_get(type);
#अगर_घोषित CONFIG_MODULES
	अगर (!ops) अणु
		up_पढ़ो(&link_ops_rwsem);
		request_module("rdma-link-%s", type);
		करोwn_पढ़ो(&link_ops_rwsem);
		ops = link_ops_get(type);
	पूर्ण
#पूर्ण_अगर
	err = ops ? ops->newlink(ibdev_name, ndev) : -EINVAL;
	up_पढ़ो(&link_ops_rwsem);
	dev_put(ndev);

	वापस err;
पूर्ण

अटल पूर्णांक nldev_dellink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	u32 index;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
				     nldev_policy, extack);
	अगर (err || !tb[RDMA_NLDEV_ATTR_DEV_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	अगर (!(device->attrs.device_cap_flags & IB_DEVICE_ALLOW_USER_UNREG)) अणु
		ib_device_put(device);
		वापस -EINVAL;
	पूर्ण

	ib_unरेजिस्टर_device_and_put(device);
	वापस 0;
पूर्ण

अटल पूर्णांक nldev_get_अक्षरdev(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	अक्षर client_name[RDMA_NLDEV_ATTR_CHARDEV_TYPE_SIZE];
	काष्ठा ib_client_nl_info data = अणुपूर्ण;
	काष्ठा ib_device *ibdev = शून्य;
	काष्ठा sk_buff *msg;
	u32 index;
	पूर्णांक err;

	err = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1, nldev_policy,
			  extack);
	अगर (err || !tb[RDMA_NLDEV_ATTR_CHARDEV_TYPE])
		वापस -EINVAL;

	nla_strscpy(client_name, tb[RDMA_NLDEV_ATTR_CHARDEV_TYPE],
		    माप(client_name));

	अगर (tb[RDMA_NLDEV_ATTR_DEV_INDEX]) अणु
		index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
		ibdev = ib_device_get_by_index(sock_net(skb->sk), index);
		अगर (!ibdev)
			वापस -EINVAL;

		अगर (tb[RDMA_NLDEV_ATTR_PORT_INDEX]) अणु
			data.port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
			अगर (!rdma_is_port_valid(ibdev, data.port)) अणु
				err = -EINVAL;
				जाओ out_put;
			पूर्ण
		पूर्ण अन्यथा अणु
			data.port = -1;
		पूर्ण
	पूर्ण अन्यथा अगर (tb[RDMA_NLDEV_ATTR_PORT_INDEX]) अणु
		वापस -EINVAL;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ out_put;
	पूर्ण
	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_GET_CHARDEV),
			0, 0);

	data.nl_msg = msg;
	err = ib_get_client_nl_info(ibdev, client_name, &data);
	अगर (err)
		जाओ out_nlmsg;

	err = nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CHARDEV,
				huge_encode_dev(data.cdev->devt),
				RDMA_NLDEV_ATTR_PAD);
	अगर (err)
		जाओ out_data;
	err = nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CHARDEV_ABI, data.abi,
				RDMA_NLDEV_ATTR_PAD);
	अगर (err)
		जाओ out_data;
	अगर (nla_put_string(msg, RDMA_NLDEV_ATTR_CHARDEV_NAME,
			   dev_name(data.cdev))) अणु
		err = -EMSGSIZE;
		जाओ out_data;
	पूर्ण

	nlmsg_end(msg, nlh);
	put_device(data.cdev);
	अगर (ibdev)
		ib_device_put(ibdev);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

out_data:
	put_device(data.cdev);
out_nlmsg:
	nlmsg_मुक्त(msg);
out_put:
	अगर (ibdev)
		ib_device_put(ibdev);
	वापस err;
पूर्ण

अटल पूर्णांक nldev_sys_get_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	err = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, extack);
	अगर (err)
		वापस err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_SYS_GET),
			0, 0);

	err = nla_put_u8(msg, RDMA_NLDEV_SYS_ATTR_NETNS_MODE,
			 (u8)ib_devices_shared_netns);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	/*
	 * Copy-on-विभाजन is supported.
	 * See commits:
	 * 70e806e4e645 ("mm: Do early cow for pinned pages during fork() for ptes")
	 * 4eae4efa2c29 ("hugetlb: do early cow when page pinned on src mm")
	 * क्रम more details. Don't backport this without them.
	 *
	 * Return value ignored on purpose, assume copy-on-विभाजन is not
	 * supported in हाल of failure.
	 */
	nla_put_u8(msg, RDMA_NLDEV_SYS_ATTR_COPY_ON_FORK, 1);

	nlmsg_end(msg, nlh);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);
पूर्ण

अटल पूर्णांक nldev_set_sys_set_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	u8 enable;
	पूर्णांक err;

	err = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, extack);
	अगर (err || !tb[RDMA_NLDEV_SYS_ATTR_NETNS_MODE])
		वापस -EINVAL;

	enable = nla_get_u8(tb[RDMA_NLDEV_SYS_ATTR_NETNS_MODE]);
	/* Only 0 and 1 are supported */
	अगर (enable > 1)
		वापस -EINVAL;

	err = rdma_compatdev_set(enable);
	वापस err;
पूर्ण

अटल पूर्णांक nldev_stat_set_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	u32 index, port, mode, mask = 0, qpn, cntn = 0;
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	ret = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, extack);
	/* Currently only counter क्रम QP is supported */
	अगर (ret || !tb[RDMA_NLDEV_ATTR_STAT_RES] ||
	    !tb[RDMA_NLDEV_ATTR_DEV_INDEX] ||
	    !tb[RDMA_NLDEV_ATTR_PORT_INDEX] || !tb[RDMA_NLDEV_ATTR_STAT_MODE])
		वापस -EINVAL;

	अगर (nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_RES]) != RDMA_NLDEV_ATTR_RES_QP)
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
	अगर (!rdma_is_port_valid(device, port)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_STAT_SET),
			0, 0);

	mode = nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_MODE]);
	अगर (mode == RDMA_COUNTER_MODE_AUTO) अणु
		अगर (tb[RDMA_NLDEV_ATTR_STAT_AUTO_MODE_MASK])
			mask = nla_get_u32(
				tb[RDMA_NLDEV_ATTR_STAT_AUTO_MODE_MASK]);
		ret = rdma_counter_set_स्वतः_mode(device, port, mask, extack);
		अगर (ret)
			जाओ err_msg;
	पूर्ण अन्यथा अणु
		अगर (!tb[RDMA_NLDEV_ATTR_RES_LQPN])
			जाओ err_msg;
		qpn = nla_get_u32(tb[RDMA_NLDEV_ATTR_RES_LQPN]);
		अगर (tb[RDMA_NLDEV_ATTR_STAT_COUNTER_ID]) अणु
			cntn = nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_COUNTER_ID]);
			ret = rdma_counter_bind_qpn(device, port, qpn, cntn);
		पूर्ण अन्यथा अणु
			ret = rdma_counter_bind_qpn_alloc(device, port,
							  qpn, &cntn);
		पूर्ण
		अगर (ret)
			जाओ err_msg;

		अगर (fill_nldev_handle(msg, device) ||
		    nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port) ||
		    nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_COUNTER_ID, cntn) ||
		    nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LQPN, qpn)) अणु
			ret = -EMSGSIZE;
			जाओ err_fill;
		पूर्ण
	पूर्ण

	nlmsg_end(msg, nlh);
	ib_device_put(device);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_fill:
	rdma_counter_unbind_qpn(device, port, qpn, cntn);
err_msg:
	nlmsg_मुक्त(msg);
err:
	ib_device_put(device);
	वापस ret;
पूर्ण

अटल पूर्णांक nldev_stat_del_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	काष्ठा ib_device *device;
	काष्ठा sk_buff *msg;
	u32 index, port, qpn, cntn;
	पूर्णांक ret;

	ret = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, extack);
	अगर (ret || !tb[RDMA_NLDEV_ATTR_STAT_RES] ||
	    !tb[RDMA_NLDEV_ATTR_DEV_INDEX] || !tb[RDMA_NLDEV_ATTR_PORT_INDEX] ||
	    !tb[RDMA_NLDEV_ATTR_STAT_COUNTER_ID] ||
	    !tb[RDMA_NLDEV_ATTR_RES_LQPN])
		वापस -EINVAL;

	अगर (nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_RES]) != RDMA_NLDEV_ATTR_RES_QP)
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
	अगर (!rdma_is_port_valid(device, port)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_STAT_SET),
			0, 0);

	cntn = nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_COUNTER_ID]);
	qpn = nla_get_u32(tb[RDMA_NLDEV_ATTR_RES_LQPN]);
	अगर (fill_nldev_handle(msg, device) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_COUNTER_ID, cntn) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_RES_LQPN, qpn)) अणु
		ret = -EMSGSIZE;
		जाओ err_fill;
	पूर्ण

	ret = rdma_counter_unbind_qpn(device, port, qpn, cntn);
	अगर (ret)
		जाओ err_fill;

	nlmsg_end(msg, nlh);
	ib_device_put(device);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_fill:
	nlmsg_मुक्त(msg);
err:
	ib_device_put(device);
	वापस ret;
पूर्ण

अटल पूर्णांक stat_get_करोit_शेष_counter(काष्ठा sk_buff *skb,
					 काष्ठा nlmsghdr *nlh,
					 काष्ठा netlink_ext_ack *extack,
					 काष्ठा nlattr *tb[])
अणु
	काष्ठा rdma_hw_stats *stats;
	काष्ठा nlattr *table_attr;
	काष्ठा ib_device *device;
	पूर्णांक ret, num_cnts, i;
	काष्ठा sk_buff *msg;
	u32 index, port;
	u64 v;

	अगर (!tb[RDMA_NLDEV_ATTR_DEV_INDEX] || !tb[RDMA_NLDEV_ATTR_PORT_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	अगर (!device->ops.alloc_hw_stats || !device->ops.get_hw_stats) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
	अगर (!rdma_is_port_valid(device, port)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_STAT_GET),
			0, 0);

	अगर (fill_nldev_handle(msg, device) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port)) अणु
		ret = -EMSGSIZE;
		जाओ err_msg;
	पूर्ण

	stats = device->port_data ? device->port_data[port].hw_stats : शून्य;
	अगर (stats == शून्य) अणु
		ret = -EINVAL;
		जाओ err_msg;
	पूर्ण
	mutex_lock(&stats->lock);

	num_cnts = device->ops.get_hw_stats(device, stats, port, 0);
	अगर (num_cnts < 0) अणु
		ret = -EINVAL;
		जाओ err_stats;
	पूर्ण

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_STAT_HWCOUNTERS);
	अगर (!table_attr) अणु
		ret = -EMSGSIZE;
		जाओ err_stats;
	पूर्ण
	क्रम (i = 0; i < num_cnts; i++) अणु
		v = stats->value[i] +
			rdma_counter_get_hwstat_value(device, port, i);
		अगर (rdma_nl_stat_hwcounter_entry(msg, stats->names[i], v)) अणु
			ret = -EMSGSIZE;
			जाओ err_table;
		पूर्ण
	पूर्ण
	nla_nest_end(msg, table_attr);

	mutex_unlock(&stats->lock);
	nlmsg_end(msg, nlh);
	ib_device_put(device);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_table:
	nla_nest_cancel(msg, table_attr);
err_stats:
	mutex_unlock(&stats->lock);
err_msg:
	nlmsg_मुक्त(msg);
err:
	ib_device_put(device);
	वापस ret;
पूर्ण

अटल पूर्णांक stat_get_करोit_qp(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			    काष्ठा netlink_ext_ack *extack, काष्ठा nlattr *tb[])

अणु
	अटल क्रमागत rdma_nl_counter_mode mode;
	अटल क्रमागत rdma_nl_counter_mask mask;
	काष्ठा ib_device *device;
	काष्ठा sk_buff *msg;
	u32 index, port;
	पूर्णांक ret;

	अगर (tb[RDMA_NLDEV_ATTR_STAT_COUNTER_ID])
		वापस nldev_res_get_counter_करोit(skb, nlh, extack);

	अगर (!tb[RDMA_NLDEV_ATTR_STAT_MODE] ||
	    !tb[RDMA_NLDEV_ATTR_DEV_INDEX] || !tb[RDMA_NLDEV_ATTR_PORT_INDEX])
		वापस -EINVAL;

	index = nla_get_u32(tb[RDMA_NLDEV_ATTR_DEV_INDEX]);
	device = ib_device_get_by_index(sock_net(skb->sk), index);
	अगर (!device)
		वापस -EINVAL;

	port = nla_get_u32(tb[RDMA_NLDEV_ATTR_PORT_INDEX]);
	अगर (!rdma_is_port_valid(device, port)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	nlh = nlmsg_put(msg, NETLINK_CB(skb).portid, nlh->nlmsg_seq,
			RDMA_NL_GET_TYPE(RDMA_NL_NLDEV,
					 RDMA_NLDEV_CMD_STAT_GET),
			0, 0);

	ret = rdma_counter_get_mode(device, port, &mode, &mask);
	अगर (ret)
		जाओ err_msg;

	अगर (fill_nldev_handle(msg, device) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, port) ||
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_MODE, mode)) अणु
		ret = -EMSGSIZE;
		जाओ err_msg;
	पूर्ण

	अगर ((mode == RDMA_COUNTER_MODE_AUTO) &&
	    nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_AUTO_MODE_MASK, mask)) अणु
		ret = -EMSGSIZE;
		जाओ err_msg;
	पूर्ण

	nlmsg_end(msg, nlh);
	ib_device_put(device);
	वापस rdma_nl_unicast(sock_net(skb->sk), msg, NETLINK_CB(skb).portid);

err_msg:
	nlmsg_मुक्त(msg);
err:
	ib_device_put(device);
	वापस ret;
पूर्ण

अटल पूर्णांक nldev_stat_get_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	पूर्णांक ret;

	ret = nlmsg_parse(nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, extack);
	अगर (ret)
		वापस -EINVAL;

	अगर (!tb[RDMA_NLDEV_ATTR_STAT_RES])
		वापस stat_get_करोit_शेष_counter(skb, nlh, extack, tb);

	चयन (nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_RES])) अणु
	हाल RDMA_NLDEV_ATTR_RES_QP:
		ret = stat_get_करोit_qp(skb, nlh, extack, tb);
		अवरोध;
	हाल RDMA_NLDEV_ATTR_RES_MR:
		ret = res_get_common_करोit(skb, nlh, extack, RDMA_RESTRACK_MR,
					  fill_stat_mr_entry);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nldev_stat_get_dumpit(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *tb[RDMA_NLDEV_ATTR_MAX];
	पूर्णांक ret;

	ret = nlmsg_parse(cb->nlh, 0, tb, RDMA_NLDEV_ATTR_MAX - 1,
			  nldev_policy, शून्य);
	अगर (ret || !tb[RDMA_NLDEV_ATTR_STAT_RES])
		वापस -EINVAL;

	चयन (nla_get_u32(tb[RDMA_NLDEV_ATTR_STAT_RES])) अणु
	हाल RDMA_NLDEV_ATTR_RES_QP:
		ret = nldev_res_get_counter_dumpit(skb, cb);
		अवरोध;
	हाल RDMA_NLDEV_ATTR_RES_MR:
		ret = res_get_common_dumpit(skb, cb, RDMA_RESTRACK_MR,
					    fill_stat_mr_entry);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rdma_nl_cbs nldev_cb_table[RDMA_NLDEV_NUM_OPS] = अणु
	[RDMA_NLDEV_CMD_GET] = अणु
		.करोit = nldev_get_करोit,
		.dump = nldev_get_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_GET_CHARDEV] = अणु
		.करोit = nldev_get_अक्षरdev,
	पूर्ण,
	[RDMA_NLDEV_CMD_SET] = अणु
		.करोit = nldev_set_करोit,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NLDEV_CMD_NEWLINK] = अणु
		.करोit = nldev_newlink,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NLDEV_CMD_DELLINK] = अणु
		.करोit = nldev_dellink,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NLDEV_CMD_PORT_GET] = अणु
		.करोit = nldev_port_get_करोit,
		.dump = nldev_port_get_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_GET] = अणु
		.करोit = nldev_res_get_करोit,
		.dump = nldev_res_get_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_QP_GET] = अणु
		.करोit = nldev_res_get_qp_करोit,
		.dump = nldev_res_get_qp_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_CM_ID_GET] = अणु
		.करोit = nldev_res_get_cm_id_करोit,
		.dump = nldev_res_get_cm_id_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_CQ_GET] = अणु
		.करोit = nldev_res_get_cq_करोit,
		.dump = nldev_res_get_cq_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_MR_GET] = अणु
		.करोit = nldev_res_get_mr_करोit,
		.dump = nldev_res_get_mr_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_PD_GET] = अणु
		.करोit = nldev_res_get_pd_करोit,
		.dump = nldev_res_get_pd_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_CTX_GET] = अणु
		.करोit = nldev_res_get_ctx_करोit,
		.dump = nldev_res_get_ctx_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_SRQ_GET] = अणु
		.करोit = nldev_res_get_srq_करोit,
		.dump = nldev_res_get_srq_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_SYS_GET] = अणु
		.करोit = nldev_sys_get_करोit,
	पूर्ण,
	[RDMA_NLDEV_CMD_SYS_SET] = अणु
		.करोit = nldev_set_sys_set_करोit,
	पूर्ण,
	[RDMA_NLDEV_CMD_STAT_SET] = अणु
		.करोit = nldev_stat_set_करोit,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NLDEV_CMD_STAT_GET] = अणु
		.करोit = nldev_stat_get_करोit,
		.dump = nldev_stat_get_dumpit,
	पूर्ण,
	[RDMA_NLDEV_CMD_STAT_DEL] = अणु
		.करोit = nldev_stat_del_करोit,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_QP_GET_RAW] = अणु
		.करोit = nldev_res_get_qp_raw_करोit,
		.dump = nldev_res_get_qp_raw_dumpit,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_CQ_GET_RAW] = अणु
		.करोit = nldev_res_get_cq_raw_करोit,
		.dump = nldev_res_get_cq_raw_dumpit,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NLDEV_CMD_RES_MR_GET_RAW] = अणु
		.करोit = nldev_res_get_mr_raw_करोit,
		.dump = nldev_res_get_mr_raw_dumpit,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

व्योम __init nldev_init(व्योम)
अणु
	rdma_nl_रेजिस्टर(RDMA_NL_NLDEV, nldev_cb_table);
पूर्ण

व्योम __निकास nldev_निकास(व्योम)
अणु
	rdma_nl_unरेजिस्टर(RDMA_NL_NLDEV);
पूर्ण

MODULE_ALIAS_RDMA_NETLINK(RDMA_NL_NLDEV, 5);
