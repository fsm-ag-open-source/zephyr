/*
 * Copyright (c) 2019 Intel corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Disable syscall tracing for all calls from this compilation unit to avoid
 * undefined symbols as the macros are not expanded recursively
 */
#define DISABLE_SYSCALL_TRACING

#include <errno.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <tracing_core.h>
#include <tracing_buffer.h>
#include <tracing_backend.h>
#include <SEGGER_RTT.h>

#ifdef CONFIG_TRACING_HANDLE_HOST_CMD
	#error "Host cmds are not supported"
#endif

static void tracing_backend_rtt_output(
	const struct tracing_backend *backend,
	uint8_t *data, uint32_t length)
{
	uint32_t written_bytes = 0;

	while (written_bytes < length) {
		written_bytes += SEGGER_RTT_Write(1, (const void*)&data[written_bytes], length-written_bytes);
	}

}

static void tracing_backend_rtt_init(void)
{

}

const struct tracing_backend_api tracing_backend_rtt_api = {
	.init = tracing_backend_rtt_init,
	.output = tracing_backend_rtt_output
};

TRACING_BACKEND_DEFINE(tracing_backend_rtt, tracing_backend_rtt_api);
