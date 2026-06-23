# GitHub Issues & Project Management
*Course Coursework: Week 1, Assignment Q6*

This document logs the details of the hypothetical GitHub issues created for this project under the milestone **"Week 1 Completion"**.

---

## 📅 Milestone: Week 1 Completion
- **Description:** Complete all GitHub setup, version control tasks, and basic LED blink assignments.
- **Due Date:** end of Week 1

---

## 🐛 Issue #1: Bug Report
* **Title:** `Bug: Blink interval not changing when potentiometer is at maximum`
* **Assignee:** `gupta-heli` (Self)
* **Labels:** `bug`, `high-priority`
* **Description:**
  When the potentiometer is turned to its maximum rotation (analog read = 1023), the LED blink delay remains stuck at the previous state and does not register the full 2000ms delay.
* **Resolution Status:** **Closed** via commit `fix: resolve potentiometer max interval bug (Fixes #1)`

---

## ✨ Issue #2: Feature Request
* **Title:** `Feature: Add RGB LED support`
* **Assignee:** `gupta-heli` (Self)
* **Labels:** `enhancement`, `feature`
* **Description:**
  Extend the current LED blink code to support an RGB LED. The RGB LED should change colors (Red -> Green -> Blue) on each blink cycle instead of just blinking a single-color LED.
* **Resolution Status:** **Open**

---

## 📈 Issue #3: Enhancement
* **Title:** `Enhancement: Log data to Serial Monitor in CSV format`
* **Assignee:** `gupta-heli` (Self)
* **Labels:** `enhancement`, `documentation`
* **Description:**
  Format the Serial Monitor output in comma-separated values (CSV) format (e.g., `blink_count,delay_ms`) to allow easy plotting or exporting to external logging software.
* **Resolution Status:** **Open**
