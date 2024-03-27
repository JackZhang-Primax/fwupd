/*
 * Copyright (C) 2018 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#include <fwupdplugin.h>

#include "fu-engine-struct.h"

#define FU_TYPE_IDLE (fu_idle_get_type())
G_DECLARE_FINAL_TYPE(FuIdle, fu_idle, FU, IDLE, GObject)

FuIdle *
fu_idle_new(void);
guint32
fu_idle_inhibit(FuIdle *self, FuIdleInhibit inhibit, const gchar *reason) G_GNUC_NON_NULL(1);
void
fu_idle_uninhibit(FuIdle *self, guint32 token) G_GNUC_NON_NULL(1);
gboolean
fu_idle_has_inhibit(FuIdle *self, FuIdleInhibit inhibit) G_GNUC_NON_NULL(1);
void
fu_idle_set_timeout(FuIdle *self, guint timeout) G_GNUC_NON_NULL(1);
void
fu_idle_reset(FuIdle *self) G_GNUC_NON_NULL(1);

/**
 * FuIdleLocker:
 * @idle:	A #FuIdle
 * @token:	A #guint32 number
 *
 * A locker to prevent daemon from shutting down on its own
 **/
typedef struct {
	FuIdle *idle;
	guint32 token;
} FuIdleLocker;

FuIdleLocker *
fu_idle_locker_new(FuIdle *self, FuIdleInhibit inhibit, const gchar *reason) G_GNUC_NON_NULL(1);
void
fu_idle_locker_free(FuIdleLocker *locker) G_GNUC_NON_NULL(1);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(FuIdleLocker, fu_idle_locker_free)
