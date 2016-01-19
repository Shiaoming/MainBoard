@echo off
if exist DEBUG del /q DEBUG
if exist FLASH del /q FLASH
if exist settings del /q settings
if exist DEBUG rd /q /s DEBUG
if exist FLASH rd /q /s FLASH
if exist settings rd /q /s settings